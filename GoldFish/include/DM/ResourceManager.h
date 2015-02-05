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

    ResourceManager(muduo::net::EventLoop* , muduo::net::InetAddress const&);

    virtual void applyResource(MessagePtr const& msg,
                               muduo::net::TcpConnectionPtr const& cliConn) = 0;

    virtual void revokeResource(MessagePtr const& msg,
                                muduo::net::TcpConnectionPtr const& cliConn) = 0;

    virtual void onApplyResourceReply(muduo::net::TcpConnectionPtr const&,
                                      MessagePtr const&,
                                      muduo::Timestamp) = 0;

    virtual void onRevokeResourceReply(muduo::net::TcpConnectionPtr const&,
                                       MessagePtr const&,
                                       muduo::Timestamp) = 0;

protected:

    muduo::net::TcpClient _rasMasterClient;
    std::vector<TcpConnectionWeakPtr> _cliConnVec;
};

#endif