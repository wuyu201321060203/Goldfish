#include <boost/bind.hpp>

#include <muduo/base/Logging.h>

#include <DM/DMServer.h>
#include <DM/RemoteDomainInfoService.h>
#include <DM/Initializer.h>

static PongMsg pong;

using namespace muduo;
using namespace muduo::net;

DMServer::DMServer(EventLop* loop , Options const& options)
    :_userInfoHandler(new UserInfoService),
     _groupInfoHandler(new GroupInfoService),
     _importConfigHandler(new DbAcceptor),
     _dcManager(&Initializer::getEventLoop() , boost::bind(&DMServer::onHeartBeat,
         this , _1 , _2 , _3)),
     _server4Client(&Initializer::getEventLoop() ,  InetAddress( Initializer::getSelfIP(),
                                    Initializer::getCliPort() ) , "server4Client"),
     _server4DC(&Initializer::getEventLoop() , InetAddress( Initializer::getSelfIP(),
         Initializer::getDCPort() ) , "server4DC")
{
    InetAddress rcAddr(Initializer::getRCIP() , Initializer::getRCPort());
    ResourceManagerPtr reourceManager(new RASTunnel(&Initializer::getEventLoop(),
        rcAddr));

    _domainInfoHandler.reset(new RemoteDomainInfoService(resourceManager));

    _server4Client.setConnectionCallback(boost::bind(&DMServer::onCliConnection,
        this , _1));

    _server4DC.setConnectionCallback(boost::bind(&DMServer::onDCConnection,
        this , _1));

    _server4Client.setMessageCallback(boost::bind(&ProtobufCodec::onMessage,
        &Initializer::getCodec() , _1 , _2 , _3));

    _server4DC.setMessageCallback(boost::bind(&ProtobufCodec::onMessage,
        &Initializer::getCodec() , _1 , _2 , _3));

    ( Initializer::getDispatcher() ).registerMessageCallback(
        PingMsg::descriptor(),
        boost::bind(&HeartBeatManager::onMessageCallback , &_dcManager , _1 , _2 , _3)
    );
}

void DMServer::start()
{
    _server4Client.start();
    _server4DC.start();
}

void DMServer::onCliConnection(TcpConnection const& conn)
{
    //TODO
}

void DMServer::onDCConnection(TcpConnection const& conn)
{
    //TODO
}

void DMServer::onHeartBeat(muduo::net::TcpConnectionPtr const& conn,
                           MessagePtr const& msg,
                           Timestamp receiveTime)
{
    ( Initializer::getCodec() ).send(conn , pong);
}