#include <muduo/base/Logging.h>

#include <DM/RASTunnel.h>
#include <DM/Initializer.h>

using namespace muduo;
using namespace muduo::net;
using namespace FwmRcProto;

#define NORMAL 1
#define ABNORMAL 0

RASTunnel::RASTunnel(muduo::net::EventLoop* loop , muduo::net::InetAddress const& serveAddr):
                     _rasMasterClient(loop , serveAddr) , _status(RAS_DISCONNECTED),
                     _rasCodec(boost::bind(&ProtobufDispatcher::onProtobufMessage,
                                &Initializer::getDispatcher() , _1 , _2 , _3) )
{
    _rasMasterClient.setConnectionCallback( boost::bind(
        &RASTunnel::onConnectionCallbackFromRC , this , _1) );

    _rasMasterClient.setMessageCallback( boost::bind(&ProtobufRASCodec::onMessage,
        &_rasCodec , _1 , _2 , _3) );

    ( Initializer::getDispatcher() ).registerMessageCallback(
        RegisterACK::descriptor(),
        boost::bind(&RASTunnel::onRegisterCallback , this , _1 , _2 , _3) );

    ( Initializer::getDispatcher() ).registerMessageCallback(
        RequestStartSlaveAck::descriptor(),
        boost::bind(&RASTunnel::onApplyResourceReply , this , _1 , _2 , _3) );

    ( Initializer::getDispatcher() ).registerMessageCallback(
        StopModuleAck::descriptor(),
        boost::bind(&RASTunnel::onRevokeResourceReply , this , _1 , _2 , _3) );
}

void RASTunnel::init()
{
    _rasMasterClient.connect();
}

void RASTunnel::applyResource(STDSTR domainName , STDSTR domainDescription,
                              double cpuNum , uint32_t cpuMemSize,
                              muduo::net::TcpConnectionPtr const& cliConn)
{
    if(NORMAL == _status)
    {
        _cliConnApplyVec.push_back(cliConn);
        RequestStartSlave apply;
        FrameworkInstanceInfo* instanceInfo =
                                        apply.mutable_framework_instance_info();

        instanceInfo->set_framework_id( Initializer::getFrameworkID() );
        instanceInfo->set_framework_instance_id( Initializer::getFrameworkInstanceID() );

        apply.set_self_module_id(Initializer::getSelfModuleID());

        EachModuleResourceInfo* moduleResourceInfo = apply.add_start_module_resource_info();
        moduleResourceInfo->set_ip("*");
        ResourceInfo* resourceInfo = moduleResourceInfo->mutable_resource_info();
        double coreNum = coreNum;
        uint32_t memSize = cpuMemSize;
        resourceInfo->set_cpu_num(coreNum);
        resourceInfo->set_cpu_mem_size(memSize);
        moduleResourceInfo->set_listen_port_num()//TODO

        NetAddress* addr = apply.mutable_fwm_net_address();
        addr->set_ip(Initializer::getSelfIP());
        addr->set_port(Initializer::getDCPort());

        DomainInfoCache tmp;
        tmp._domainName = domainName;
        tmp._domainDescription = domainDescription;
        tmp._cpuNum = coreNum;
        tmp._cpuMemSize = memSize;
        _cacheVec.push_back(tmp);

        (Initializer::getCodec()).send(_rasMasterClient.connection() , apply);
    }
    else
        onFailSend<DomainCreateACK>(cliConn , RESOURCE_APPLY_FAIL);
}

void RASTunnel::revokeResource(uint32_t domainID,
                               muduo::net::TcpConnectionPtr const& cliConn)
{
    if(NORMAL == _status)
    {
        _cliConnRevokeVec.push_back(cliConn);
        StopModule query;
        FrameworkInstanceInfo* instanceInfo = query.mutable_framework_instance_info();
        instanceInfo->set_framework_id( Initializer::getFrameworkID() );
        instanceInfo->set_framework_instance_id( Initializer::getFrameworkInstanceID() );
        query.set_self_module_id(Initializer::getSelfModuleID());
        query.set_stop_module_id(domainID);
        (Initializer::getCodec()).send(_rasMasterClient.connection() , query);
    }
    else
        onFailSend<DomainDestroyACK>(cliConn , RESOURCE_REVOKE_FAIL);
}

void RASTunnel::onApplyResourceReply(muduo::net::TcpConnectionPtr const& conn,
                                     MessagePtr const& msg,
                                     muduo::Timestamp receiveTime)
{
    boost::shared_ptr<RequestStartSlaveAck> respond =
        muduo::down_pointer_cast<RequestStartSlaveAck>(msg);

    TcpConnectionWeakPtr tmp = _cliConnApplyVec.front();
    _cliConnApplyVec.erase(_cliConnApplyVec.begin());
    TcpConnectionPtr cliConn(tmp.lock());
    if(cliConn)
    {
        if(RESOURCE_APPLY_FAIL !=  respond->statuscode())
        {
            if(0 < _cacheVec.size())
            {
                DomainInfoCache cache = _cacheVec.front();
                _cacheVec.erase(_cacheVec.begin())
                    (Initializer::getThreadPool()).run(boost::bind(&RASTunnel::doCreateDomain,
                        this , cliConn , respond.module_id(),
                        cache._domainName,
                        cache._domainDescription,
                        cache._cpuNum,
                        cache._cpuMemSize));

                return;
            }
        }
        onFailSend<DomainCreateACK>(cliConn , RESOURCE_APPLY_FAIL);
    }
}

void RASTunnel::onRevokeResourceReply(muduo::net::TcpConnectionPtr const& conn,
                                      MessagePtr const& msg,
                                      muduo::Timestamp receiveTime)
{
    boost::shared_ptr<StopModuleAck> respond =
        muduo::down_pointer_cast<StopModuleAck>(msg);

    TcpConnectionWeakPtr tmp = _cliConnApplyVec.front();
    _cliConnApplyVec.erase(_cliConnApplyVec.begin());
    TcpConnectionPtr cliConn(tmp.lock());
    if(cliConn)
    {
        if(RESOURCE_REVOKE_FAIL !=  respond->statuscode())
        {
            (Initializer::getThreadPool()).run(boost::bind(&RASTunnel::doRevokeDomain,
                    this , respond->stop_module_id() , cliConn) );
        }
        else
            onFailSend<DomainDestroyACK>(cliConn , RESOURCE_REVOKE_FAIL);
    }
}

void RASTunnel::onConnectionCallbackFromRC(TcpConnectionPtr const& conn)
{
    if(conn->connected())
    {
        //heartbeat
        register2RAS(conn);
    }
    else
    {
        LOG_INFO << "disconnect to RC of RAS";
        _status = RAS_DISCONNECTED;
    }
}

void RASTunnel::register2RAS(TcpConnectionPtr const& conn)
{
    Register msg;
    FrameworkInstanceInfo* instanceInfo = msg.mutable_framework_instance_info();
    instanceInfo->set_framework_id(Initializer::getFrameworkID());
    instanceInfo->set_framework_instance_id(Initializer::getFrameworkInstanceID());
    msg.set_self_module_id(Initializer::getSelfModuleID());
    ( Initializer::getCodec() ).send(conn , msg);
}

void RASTunnel::onRegisterCallback(TcpConnectionPtr const& conn,
                                   MessagePtr const& msg,
                                   muduo::Timestamp receiveTime)
{
    boost::shared_ptr<RegisterACK> reply = muduo::down_pointer_cast<RegisterACK>(msg);

    if(SUCCESS == reply->statuscode()) _status = NORMAL;
    else
    {
        _status = ABNORMAL;
        LOG_INFO << "failed to register to RAS";
    }
}

void RASTunnel::doCreateDomain(TcpConnectionPtr const& conn , uint32_t domainID,
                               STDSTR domainName , STDSTR domainDescription,
                               double cpuNum , uint32_t cpuMemSize)
{
    ConnectionPtr dbConn = (Initializer::getDbPool()).getConnection<MysqlConnection>();
    ResultSetPtr result;
    DomainCreateACK reply;
    try
    {
        {
            MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
            MutexLockGuard guard(**lock);
            result = dbConn->executeQuery("select id from DOMAIN_INFO\
                where name = '%s' " , domainName.c_str());
                if( !result->next() )
                {
                    dbConn->execute("insert into DOMAIN_INFO(id , name , description,\
                        corenum , memsize) values('%d' , '%s', '%s' , '%ld' , '%d')",
                         domainID , domainName.c_str() , domainDescription.c_str(),
                         cpuNum , cpuMemSize);

                    reply.set_statuscode(SUCCESS);
                    reply.set_domainid(domainID);
                }
                else
                    reply.set_statuscode(EXISTED_DOMAIN);
        }
    }
    catch(SQLException const& e)
    {
#ifdef TEST
        std::cout << e.getReason() << "\n";
#endif

        reply.set_statuscode(UNKNOWN_SYSERROR);
    }
    dbConn->close();
#ifndef TEST
    ( Initializer::getCodec() ).send(conn , reply);
#endif
}

void RASTunnel::doRevokeDomain(TcpConnectionPtr const& conn , uint32_t domainID)
{
    ConnectionPtr dbConn = (Initializer::getDbPool()).getConnection<MysqlConnection>();
    ResultSetPtr result;
    DomainDestroyACK reply;
    try
    {
        {
            MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
            MutexLockGuard guard(**lock);
            dbConn->execute("delete from DOMAIN_INFO where id = '%d' " , domainID);
        }
    }
    catch(SQLException const& e)
    {
#ifdef TEST
        std::cout << e.getReason() << "\n";
#endif

        reply.set_statuscode(UNKNOWN_SYSERROR);
    }
    dbConn->close();
#ifndef TEST
    ( Initializer::getCodec() ).send(conn , reply);
#endif
}