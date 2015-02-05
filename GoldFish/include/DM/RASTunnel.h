#ifndef RASTUNNEL_H
#define RASTUNNEL_H

#include "ReourceManager.h"

class RASTunnel : public ResourceManager
{
public:

    RASTunnel(muduo::net::EventLoop* , muduo::net::InetAddress const&);

    virtual void applyResource(MessagePtr const& msg,
                               muduo::net::TcpConnectionPtr const& cliConn);

    virtual void revokeResource(MessagePtr const& msg,
                                muduo::net::TcpConnectionPtr const& cliConn);

    virtual void onApplyResourceReply(muduo::net::TcpConnectionPtr const&,
                                      MessagePtr const&,
                                      muduo::Timestamp);

    virtual void onRevokeResourceReply(muduo::net::TcpConnectionPtr const&,
                                       MessagePtr const&,
                                       muduo::Timestamp);
};

#endif