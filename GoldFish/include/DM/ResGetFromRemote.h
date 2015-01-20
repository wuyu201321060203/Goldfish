#ifndef RESGETFROMREMOTE_H
#define RESGETFROMREMOTE_H

#include <vector>

#include <muduo/net/TcpConnection.h>

#include "ResGetStrategy.h"

class ResGetFromRemote : public ResGetStrategy
{
public:

    ResGetFromRemote(EventLoop* , InetAddress const& , string const&);
    virtual void applyResource(MessagePtr const& , TcpConnectionPtr const&);
    virtual void revokeResource(MessagePtr const&, TcpConnectionPtr const&);
    void onApplyResourceACK(TcpConnectionPtr const& , MessagePtr const& , Timestamp);
    void onRevokeResourceACK(TcpConnectionPtr const& , MessagePtr const& , Timestamp);

private:

    TcpClient _client;
    std::vector<TcpConnectionWeakPtr> _cliConnVec;
    std::vector<MessagePtr> _msgVec;
};

#endif