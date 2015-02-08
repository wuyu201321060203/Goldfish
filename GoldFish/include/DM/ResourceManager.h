#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <vector>

#include <muduo/net/TcpConnection.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpClient.h>

#include "Config.h"

class ResourceManager
{
public:

    virtual void init();

    virtual void applyResource(MessagePtr const& msg,
                               muduo::net::TcpConnectionPtr const& cliConn) = 0;

    virtual void revokeResource(MessagePtr const& msg,
                                muduo::net::TcpConnectionPtr const& cliConn) = 0;
};

#endif