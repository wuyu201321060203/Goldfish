#ifndef RASSERVER_H
#define RASSERVER_H

#include <muduo/net/EventLoop.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/TcpServer.h>

#include <mysql/MysqlConnection.h>
#include <Exception/SQLException.h>

#include <DM/RASTunnel.h>
#include <DM/Initializer.h>
#include <DM/ProtobufRASCodec.h>
#include <DM/ProtobufDispatcher.h>
#include <DM/Config.h>

using namespace muduo;
using namespace muduo::net;
using namespace FwmRcProto;
using namespace OOzdb;
using boost::any_cast;


using namespace muduo;
using namespace muduo::net;

#define RESOURCE_APPLY_SUCCESS 0
#define RESOURCE_REVOKE_SUCCESS 0

class RASServer
{
public:

    RASServer(EventLoop* loop , InetAddress const& listenAddr)
        :_server(loop , listenAddr , "RASServer"),
         _codec(boost::bind(&ProtobufDispatcher::onProtobufMessage,
                            &_dispatcher , _1 , _2 , _3)),
         _dispatcher(boost::bind(&RASServer::onUnknownMessage , this , _1 , _2 , _3))
    {
        Initializer::registeRASMsg(MSG_FWM_RC_REGISTER , "FwmRcProto.Register");
        Initializer::registeRASMsg(MSG_FWM_RC_REGISTER_ACK , "FwmRcProto.RegisterAck");

        Initializer::registeRASMsg(MSG_FWM_RC_REQUEST_START_SLAVE,
            "FwmRcProto.RequestStartSlave");

        Initializer::registeRASMsg(MSG_FWM_RC_REQUEST_START_SLAVE_ACK,
            "FwmRcProto.RequestStartSlaveAck");

        Initializer::registeRASMsg(MSG_FWM_RC_STOP_MODULE , "FwmRcProto.StopModule");
        Initializer::registeRASMsg(MSG_FWM_RC_STOP_MODULE_ACK , "FwmRcProto.StopModuleAck");
        Initializer::registeRASMsg(MSG_FWM_RC_SEND_HEARTBEAT , "FwmRcProto.HeartBeatInfo");
        Initializer::registeRASMsg(MSG_FWM_RC_SEND_HEARTBEAT_ACK,
            "FwmRcProto.HeartBeatInfoAck");

        _dispatcher.registerMessageCallback(Register::descriptor(),
            boost::bind(&RASServer::onRegister , this , _1 , _2 , _3));

        _dispatcher.registerMessageCallback(RequestStartSlave::descriptor(),
            boost::bind(&RASServer::onApplyResource , this , _1 , _2 , _3));

        _dispatcher.registerMessageCallback(StopModule::descriptor(),
            boost::bind(&RASServer::onRevokeResource , this , _1 , _2 , _3));

        _server.setConnectionCallback(
            boost::bind(&RASServer::onConnection , this , _1));

        _server.setMessageCallback(
            boost::bind(&ProtobufRASCodec::onMessage, &_codec, _1, _2, _3));
    }

    void start()
    {
        _server.start();
    }

private:

    TcpServer _server;
    ProtobufRASCodec _codec;
    ProtobufDispatcher _dispatcher;

private:

    void onConnection(TcpConnectionPtr const& conn)
    {
        LOG_INFO << conn->localAddress().toIpPort() << " -> " << conn->peerAddress().toIpPort() << " is " <<
            (conn->connected() ? "UP" : "DOWN");
    }

    void onRegister(TcpConnectionPtr const& conn , MessagePtr const& msg,
                    Timestamp receiveTime)
    {
        RegisterAck reply;
        reply.set_statuscode(SUCCESS);
#ifdef TEST
        LOG_INFO << "Someone Registe!";
#endif
        _codec.send(conn , reply);
    }

    void onApplyResource(TcpConnectionPtr const& conn , MessagePtr const& msg,
                         Timestamp receiveTime)
    {
        RequestStartSlaveAck reply;
        reply.set_statuscode(RESOURCE_APPLY_SUCCESS);
        reply.add_module_id(66);
        _codec.send(conn , reply);
    }

    void onRevokeResource(TcpConnectionPtr const& conn , MessagePtr const& msg,
                          Timestamp receiveTime)
    {
        StopModuleAck reply;
        reply.set_statuscode(RESOURCE_REVOKE_SUCCESS);
        reply.add_stop_module_id(66);
        _codec.send(conn , reply);
    }

    void onUnknownMessage(TcpConnectionPtr const& conn , MessagePtr const& msg,
                          Timestamp receiveTime)
    {
        LOG_INFO << "onUnknownMessage:" << msg->GetTypeName();
    }
};

#endif