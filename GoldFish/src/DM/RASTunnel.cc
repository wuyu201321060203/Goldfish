#ifdef TEST
#include <unistd.h>//TODO
#include <iostream>//TODO
#endif

#ifdef DMDEBUG
#include <muduo/base/Logging.h>
#endif

#include <mysql/MysqlConnection.h>
#include <Exception/SQLException.h>

#include <DM/RASTunnel.h>
#include <DM/Initializer.h>

using namespace muduo;
using namespace muduo::net;
using namespace FwmRcProto;
using namespace OOzdb;
using boost::any_cast;

#define NORMAL 1
#define ABNORMAL 0

static HeartBeatInfo ping;

RASTunnel::RASTunnel(EventLoop* loop , InetAddress const& serveAddr):
                     _rasMasterClient(loop , serveAddr , "rasMasterClient"),
                     _status(ABNORMAL),
                     _rasCodec(boost::bind(&ProtobufDispatcher::onProtobufMessage,
                                &Initializer::getDispatcher() , _1 , _2 , _3) ),
                     _hbManager(loop , boost::bind(&RASTunnel::onHeartBeat , this,
                                                _1 , _2 , _3) )
{
    _rasMasterClient.setConnectionCallback( boost::bind(
        &RASTunnel::onConnectionCallbackFromRC , this , _1) );

    _rasMasterClient.setMessageCallback( boost::bind(&ProtobufRASCodec::onMessage,
        &_rasCodec , _1 , _2 , _3) );

    ProtobufRASCodec::registeRASMsg(MSG_FWM_RC_REGISTER , "FwmRcProto.Register");
    ProtobufRASCodec::registeRASMsg(MSG_FWM_RC_REGISTER_ACK , "FwmRcProto.RegisterAck");

    ProtobufRASCodec::registeRASMsg(MSG_FWM_RC_REQUEST_START_SLAVE,
                               "FwmRcProto.RequestStartSlave");

    ProtobufRASCodec::registeRASMsg(MSG_FWM_RC_REQUEST_START_SLAVE_ACK,
                               "FwmRcProto.RequestStartSlaveAck");

    ProtobufRASCodec::registeRASMsg(MSG_FWM_RC_STOP_MODULE , "FwmRcProto.StopModule");
    ProtobufRASCodec::registeRASMsg(MSG_FWM_RC_STOP_MODULE_ACK , "FwmRcProto.StopModuleAck");
    ProtobufRASCodec::registeRASMsg(MSG_FWM_RC_SEND_HEARTBEAT , "FwmRcProto.HeartBeatInfo");
    ProtobufRASCodec::registeRASMsg(MSG_FWM_RC_SEND_HEARTBEAT_ACK,
                               "FwmRcProto.HeartBeatInfoAck");

    ( Initializer::getDispatcher() ).registerMessageCallback(
        RegisterAck::descriptor(),
        boost::bind(&RASTunnel::onRegisterCallback , this , _1 , _2 , _3) );

    ( Initializer::getDispatcher() ).registerMessageCallback(
        RequestStartSlaveAck::descriptor(),
        boost::bind(&RASTunnel::onApplyResourceReply , this , _1 , _2 , _3) );

    ( Initializer::getDispatcher() ).registerMessageCallback(
        StopModuleAck::descriptor(),
        boost::bind(&RASTunnel::onRevokeResourceReply , this , _1 , _2 , _3) );

    ( Initializer::getDispatcher() ).registerMessageCallback(
        HeartBeatInfoAck::descriptor(),
        boost::bind(&HeartBeatManager::onMessageCallback , &_hbManager , _1 , _2 , _3) );

    FrameworkInstanceInfo* instanceInfo = ping.mutable_framework_instance_info();
    instanceInfo->set_framework_id(Initializer::getFrameworkID());
    instanceInfo->set_framework_instance_id(Initializer::getFrameworkInstanceID());
    ping.set_self_module_id(Initializer::getSelfModuleID());
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
        moduleResourceInfo->set_start_module_name("/Goldfish/DC");
        moduleResourceInfo->set_ip("*");
        ResourceInfo* resourceInfo = moduleResourceInfo->mutable_resource_info();
        double coreNum = cpuNum;
        uint32_t memSize = cpuMemSize;
        resourceInfo->set_cpu_num(coreNum);
        resourceInfo->set_cpu_mem_size(memSize);
        moduleResourceInfo->set_listen_port_num(4);//DC need 4 ports to serve

        NetAddress* addr = apply.mutable_fwm_net_address();
        addr->set_ip(Initializer::getSelfIP());
        addr->set_port(Initializer::getDCPort());

        DomainInfoCache tmp;
        tmp._domainName = domainName;
        tmp._domainDescription = domainDescription;
        tmp._cpuNum = coreNum;
        tmp._cpuMemSize = memSize;
        _cacheVec.push_back(tmp);

        _rasCodec.send(_rasMasterClient.connection() , apply);
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
        query.add_stop_module_id(domainID);
        _rasCodec.send(_rasMasterClient.connection() , query);
    }
    else
        onFailSend<DomainDestroyACK>(cliConn , RESOURCE_REVOKE_FAIL);
}

void RASTunnel::onApplyResourceReply(muduo::net::TcpConnectionPtr const& conn,
                                     MessagePtr const& msg,
                                     muduo::Timestamp receiveTime)
{
    _hbManager.resetTimerTask(conn);
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
                _cacheVec.erase(_cacheVec.begin());
                uint32_t moduleID = respond->module_id(0);

#ifdef DMDEBUG
                LOG_INFO << "main apply";
#endif
                (Initializer::getThreadPool()).run(boost::bind(&RASTunnel::doCreateDomain,
                    this , cliConn , moduleID,
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
    _hbManager.resetTimerTask(conn);
    boost::shared_ptr<StopModuleAck> respond =
        muduo::down_pointer_cast<StopModuleAck>(msg);

    TcpConnectionWeakPtr tmp = _cliConnRevokeVec.front();
    _cliConnRevokeVec.erase(_cliConnRevokeVec.begin());
    TcpConnectionPtr cliConn(tmp.lock());
    if(cliConn)
    {
        if(RESOURCE_REVOKE_FAIL !=  respond->statuscode())
        {
#ifdef DMDEBUG
            LOG_INFO << "main revoke";
#endif
            (Initializer::getThreadPool()).run(boost::bind(&RASTunnel::doRevokeDomain,
                    this , cliConn , respond->stop_module_id(0)) );
        }
        else
            onFailSend<DomainDestroyACK>(cliConn , RESOURCE_REVOKE_FAIL);
    }
}

#ifdef TEST
TcpConnectionPtr RASTunnel::getConn()
{
    return _rasMasterClient.connection();
}
#endif

void RASTunnel::onConnectionCallbackFromRC(TcpConnectionPtr const& conn)
{
    if(conn->connected())
    {
        register2RAS(conn);
    }
    else
    {
#ifdef DMDEBUG
        LOG_INFO << "disconnect to RC of RAS";
#endif
        _status = ABNORMAL;
    }
}

void RASTunnel::register2RAS(TcpConnectionPtr const& conn)
{
    Register msg;
    FrameworkInstanceInfo* instanceInfo = msg.mutable_framework_instance_info();
    instanceInfo->set_framework_id(Initializer::getFrameworkID());
    instanceInfo->set_framework_instance_id(Initializer::getFrameworkInstanceID());
    msg.set_self_module_id(Initializer::getSelfModuleID());
    NetAddress* addr = msg.mutable_data_search_entry();
    addr->set_ip(Initializer::getSelfIP());
    addr->set_port(Initializer::getCliPort());
    _rasCodec.send(conn , msg);
}

void RASTunnel::onRegisterCallback(TcpConnectionPtr const& conn,
                                   MessagePtr const& msg,
                                   muduo::Timestamp receiveTime)
{
    boost::shared_ptr<RegisterAck> reply = muduo::down_pointer_cast<RegisterAck>(msg);

    if(SUCCESS == reply->statuscode())
    {
        _status = NORMAL;
        _rasCodec.send(conn , ping);
        _hbManager.delegateTimerTask(2 , 10 , 3,
                    boost::bind(&RASTunnel::onTimeout , this) , conn);
#ifdef DMDEBUG
        LOG_INFO << "register to RAS success";
#endif
#ifdef TEST
        applyResource("domain2" , "domain2" , 1 , 1 , getConn());
        revokeResource(66 , getConn());
#endif
    }
    else
    {
        _status = ABNORMAL;
#ifdef DMDEBUG
        LOG_INFO << "failed to register to RAS";
#endif
    }
}

void RASTunnel::doCreateDomain(TcpConnectionPtr const& conn , uint32_t domainID,
                               STDSTR domainName , STDSTR domainDescription,
                               double cpuNum , uint32_t cpuMemSize)
{
    ConnectionPtr dbConn = (Initializer::getDbPool()).getConnection<MysqlConnection>();
    DomainCreateACK reply;
    try
    {
#ifdef DMDEBUG
        LOG_INFO << "Apply!!!!!";
#endif
        ResultSetPtr result = dbConn->executeQuery("select id from DOMAIN_INFO\
            where name = '%s' " , domainName.c_str());
        if( !result->next() )
        {
            dbConn->execute("insert into DOMAIN_INFO(id , name , description,\
                corenum , memsize) values('%d' , '%s', '%s' , '%lf' , '%d')",
                domainID , domainName.c_str() , domainDescription.c_str(),
                cpuNum , cpuMemSize);

            reply.set_statuscode(SUCCESS);
            reply.set_domainid(domainID);//need clients store
        }
        else
            reply.set_statuscode(EXISTED_DOMAIN);
        //}
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
    DomainDestroyACK reply;
    try
    {
#ifdef DMDEBUG
        LOG_INFO << "Revoke!!!!!!";
#endif
        dbConn->execute("delete from DOMAIN_INFO where id = '%d' " , domainID);
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

void RASTunnel::onHeartBeat(TcpConnectionPtr const& conn , MessagePtr const& msg,
                            Timestamp receiveTime)
{
    _rasCodec.send(conn , ping);
}

void RASTunnel::onTimeout(void)
{
#ifdef DMDEBUG
    LOG_INFO << "disconnect to RC of RAS , HeartBeat timeout";
#endif
}