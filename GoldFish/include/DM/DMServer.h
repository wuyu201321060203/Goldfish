#ifndef DM_SERVER__H
#define DM_SERVER__H

#include <boost/shared_ptr.hpp>

#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

#include "GenericInfoService.h"
#include "CustomizedServiceAcceptor.h"
#include "CrossInfoService.h"
#include "CrossDomainInfoService.h"
#include "HeartBeatManager.h"
#include "UserManager.h"
#include "Options.h"
#include "DCRegister.h"
#include "Config.h"

typedef boost::shared_ptr<GenericInfoService> GenericInfoServicePtr;

class DMServer
{
public:

    DMServer(muduo::net::EventLoop* , Options const&);
    void start();
    void onCliConnection(muduo::net::TcpConnectionPtr const&);
    void onDCConnection(muduo::net::TcpConnectionPtr const&);

private:

    GenericInfoServicePtr _userInfoHandler;
    GenericInfoServicePtr _domainInfoHandler;
    GenericInfoServicePtr _groupInfoHandler;

    CustomizedServiceAcceptorPtr _importConfigHandler;

    /*
    CrossInfoService<CrossDbInfoGetMsg , CrossDbInfoGetACK,
                     DomainDbInfoGetMsg , DomainDbInfoGetACK> _sysInfoHandler;//TODO

    CrossInfoService<CrossSysInfoGetMsg , CrossSysInfoGetACK,
                     DomainSysInfoGetMsg , DomainSysInfoGetACK> _dbInfoHandler;///TODO
                     */


    CrossDomainInfoServicePtr _sysInfoHandler;
    CrossDomainInfoServicePtr _dbInfoHandler;

    DCRegister _dcRegister;

    UserManager _userManager;
    HeartBeatManager _dcManager;

private:

    muduo::net::TcpServer _server4Client;
    muduo::net::TcpServer _server4DC;

private:

    void onHeartBeat(muduo::net::TcpConnectionPtr const&,
                     MessagePtr const&,
                     muduo::Timestamp);
};

#endif