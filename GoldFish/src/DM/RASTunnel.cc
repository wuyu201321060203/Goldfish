#include <DM/RASTunnel.h>

using namespace muduo;
using namespace muduo::net;

#define RAS_CONNECTED 1
#define RAS_DISCONNECTED 0

RASTunnel::RASTunnel(muduo::net::EventLoop* loop , muduo::net::InetAddress const& serveAddr):
                     _rasMasterClient(loop , serveAddr) , _status(RAS_DISCONNECTED),
                     _rasCodec(boost::bind(&ProtobufDispatcher::onProtobufMessage,
                                &Initializer::getDispatcher() , _1 , _2 , _3) )
{
    ( Initializer::getDispatcher() ).registerMessageCallback(
        FwmRcProto::FWMRCRegister::descriptor(),
        boost::bind(&RASTunnel::onRegisterCallback , this , _1 , _2 , _3));

    ( Initializer::getDispatcher() ).registerMessageCallback(
        FwmRcProto::RespondRequestSlaveResource::descriptor(),
        boost::bind(&RASTunnel::onApplyResourceReplyFromRC , this , _1 , _2 , _3));

    _rasMasterClient.setConnectionCallback(boost::bind(&RASTunnel::onConnectionCallbackFromRC,
        this , _1));
}

void RASTunnel::init()
{
    _rasMasterClient.connect();
}

void RASTunnel::applyResource(STDSTR domainName , STDSTR domainDescription,
                              double cpuNum , uint32_t cpuMemSize,
                              muduo::net::TcpConnectionPtr const& cliConn)
{
    if(RAS_CONNECTED == _status)
    {
        _cliConnApplyVec.push_back(cliConn);
        RequestSlaveResource apply;
        ::FwmRcProto::FrameworkInstanceInfo* frameWorkInstanceInfo =
            apply.mutable_framework_instance_info();

        frameWorkInstanceInfo->set_framework_id(Initializer::getFrameworkID());
        frameWorkInstanceInfo->set_framework_instance_id(
            Initializer::getFrameworkInstanceID());

        apply.set_module_name("DC");
        ::FwmRcProto::EachMachineResourceInfo* eachResourceInfo =
            apply.add_each_resource_info();
        eachResourceInfo->set_ip("*");
        ::FwmRcProto::ResourceInfo* resourceInfo = eachResourceInfo->mutable_resource_info();
        double coreNum = coreNum;
        uint32_t memSize = cpuMemSize;
        resourceInfo->set_cpu_num(coreNum);
        resourceInfo->set_cpu_mem_size(memSize);
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
    if(RAS_CONNECTED == _status)
    {
        _cliConnRevokeVec.push_back(cliConn);
        StopModuleInfo query;
        query.set_module_id(domainID);
        (Initializer::getCodec()).send(_rasMasterClient.connection() , query);
    }
    else
        onFailSend<DomainDestroyACK>(cliConn , RESOURCE_REVOKE_FAIL);
}

void RASTunnel::onApplyResourceReply(muduo::net::TcpConnectionPtr const& conn,
                                     MessagePtr const& msg,
                                     muduo::Timestamp receiveTime)
{
    boost::shared_ptr<RespondRequestSlaveResource> respond =
        muduo::down_pointer_cast<RespondRequestSlaveResource>(msg);

    TcpConnectionPtr cliConn = _cliConnApplyVec.front();
    _cliConnApplyVec.erase(_cliConnApplyVec.begin());

    if(RESOURCE_APPLY_FAIL !=  respond->statuscode())
    {
        if(0 < _cacheVec.size())
        {
            DomainInfoCache cache = _cacheVec.front();
            _cacheVec.erase(_cacheVec.begin())
            (Initializer::getThreadPool()).run(boost::bind(&RASTunnel::doCreateDomain,
                this , cliConn , respond.id(),//TODO
                cache._domainName,
                cache._domainDescription,
                cache._cpuNum,
                cache._cpuMemSize,
                respond.netaddress().ip(),
                respond.netaddress.port()));

            return;
        }
    }
    onFailSend<DomainCreateACK>(cliConn , RESOURCE_APPLY_FAIL);
}

void RASTunnel::onRevokeResourceReply(muduo::net::TcpConnectionPtr const& conn,
                                      MessagePtr const& msg,
                                      muduo::Timestamp receiveTime)
{
    boost::shared_ptr<MSG_FWM_RC_STOP_MODULE_ACK> respond =
        muduo::down_pointer_cast<MSG_FWM_RC_STOP_MODULE_ACK>(msg);//TODO

    TcpConnectionPtr cliConn = _cliConnApplyVec.front();
    _cliConnApplyVec.erase(_cliConnApplyVec.begin());

    if(RESOURCE_REVOKE_FAIL !=  respond->statuscode())
    {
        if(0 < _cacheVec.size())
        {
            (Initializer::getThreadPool()).run(boost::bind(&RASTunnel::doRevokeDomain,
                resopnd->module_id() ) );
            return;
        }
    }
    onFailSend<DomainDestroyACK>(cliConn , RESOURCE_REVOKE_FAIL);
}

void RASTunnel::onConnectionCallbackFromRC(TcpConnectionPtr const& conn)
{
    if(conn->connected())
    {
        _status = RAS_CONNECTED;
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
    FwmRcProto::FWMRCRegister msg;
    (msg.mutable_framework_instance_info())->set_framework_id(
                                                Initializer::getFrameworkID());

    (msg.mutable_framework_instance_info())->set_framework_instance_id(
                                        Initializer::getFrameworkInstanceID());

    (msg.mutable_framework_master_info())->set_module_name(MODULE_NAME);
    (msg.mutable_framework_master_info())->set_fw_master_ip(Initializer::getDMIP());
    ( Initializer::getCodec() ).send(conn , msg);
}

void RASTunnel::onRegisterCallback(TcpConnectionPtr const& conn,
                                   MessagePtr const& msg,
                                   muduo::Timestamp receiveTime)
{
    boost::shared_ptr<FWMRCRegisterACK> reply =
        muduo::down_pointer_cast<FWMRCRegisterACK>(msg);
    if(SUCCESS != reply->statuscode())
    {
        _statuc = RAS_DISCONNECTED;
        LOG_INFO << "failed to register to RAS";
    }
}

void RASTunnel::doCreateDomain(TcpConnectionPtr const& conn , uint32_t domainID,
                               STDSTR domainName , STDSTR domainDescription,
                               double cpuNum , uint32_t cpuMemSize,
                               STDSTR IP , uint32_t port)
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
                    dbConn->execute("insert into DOMAIN_INFO values('%d' , '%s',\
                        '%s' , '%ld' , '%d' , '%s' , '%d')",
                         domainID , domainName.c_str() , domainDescription.c_str(),
                         cpuNum , cpuMemSize , IP.c_str() , port);

                    reply.set_statuscode(SUCCESS);
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