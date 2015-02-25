#ifndef DM_SERVER__H
#define DM_SERVER__H

#include <string>

#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

#include "GenericInfoService.h"
#include "CustomizedServiceAcceptor.h"
#include "CrossDomainInfoService.h"
#include "HeartBeatManager.h"
#include "UserManager.h"
#include "Options.h"

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
    CrossDomainInfoServicePtr  _SysInfoHandler;
    CrossDomainInfoServicePtr  _DbInfoHandler;
    UserManager _userManager;
    HeartBeatManager _dcManager;

private:

    TcpServer _cliServer;
    TcpServer _dcServer;
};

#endif