#ifndef RASTUNNEL_H
#define RASTUNNEL_H

#include <vector>

#include <boost/shared_ptr.hpp>

#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpClient.h>
#include <muduo/base/Timestamp.h>

#include <DM/ProtobufRASCodec.h>

typedef boost::shared_ptr<muduo::net::TcpClient> TcpClientPtr;

#include "ReourceManager.h"

class RASTunnel : public ResourceManager
{
public:

    RASTunnel(muduo::net::EventLoop* , muduo::net::InetAddress const&);

    virtual void init();

    virtual void applyResource(MessagePtr const& msg,
                               muduo::net::TcpConnectionPtr const& cliConn);

    virtual void revokeResource(MessagePtr const& msg,
                                muduo::net::TcpConnectionPtr const& cliConn);

    void onApplyResourceReply(muduo::net::TcpConnectionPtr const&,
                                      MessagePtr const&,
                                      muduo::Timestamp);

    void onRevokeResourceReply(muduo::net::TcpConnectionPtr const&,
                                       MessagePtr const&,
                                       muduo::Timestamp);

private:

    muduo::net::TcpClient _rasMasterClient;
    std::vector<TcpClientPtr> _rasSlaveClientVec;
    std::vector<TcpConnectionWeakPtr> _cliConnVec;
    int _status;
    ProtobufRASCodec _rasCodec;
    bool _waiting4NcReply;

private:

    void onConnectionCallback(muduo::net::TcpConnectionPtr const&);
    void register2RAS(muduo::net::TcpConnectionPtr const&);
};

#endif