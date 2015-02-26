#ifndef DM_SERVER__H
#define DM_SERVER__H

#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

#include "GenericInfoService.h"
#include "CustomizedServiceAcceptor.h"
#include "CrossInfoService.h"
#include "HeartBeatManager.h"
#include "UserManager.h"
#include "Options.h"
#include "DCRegister"
#include "Config.h"

class DMServer
{
public:

    DMServer(EventLop* , Options const&);
    void start();
    void onCliConnection(TcpConnection const&);
    void onDCConnection(TcpConnection const&);

private:

    GenericInfoServicePtr _userInfoHandler;
    GenericInfoServicePtr _domainInfoHandler;
    GenericInfoServicePtr _groupInfoHandler;

    CustomizedServiceAcceptorPtr _importConfigHandler;

    CrossInfoService<CrossDbInfoGetMsg , CrossDbInfoGetACK,
                     DomainDbInfoGetMsg , DomainDbInfoGetACK> _SysInfoHandler;//TODO

    CrossInfoService<CrossSysInfoGetMsg , CrossSysInfoGetACK
                     DomainSysInfoGetMsg , DomainSysInfoGetACK> _DbInfoHandler;///TODO

    DCRegister _dcRegister;

    UserManager _userManager;
    HeartBeatManager _dcManager;

private:

    TcpServer _server4Client;
    TcpServer _server4DC;

private:

    void onHeartBeat(muduo::net::TcpConnectionPtr const&,
                     MessagePtr const&,
                     muduo::Timestamp);
};

#endif