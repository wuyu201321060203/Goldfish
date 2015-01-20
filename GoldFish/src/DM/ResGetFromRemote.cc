#include "ResGetFromRemote.h"

ResGetFromRemote::ResGetFromRemote(EventLoop* loop , InetAddress const& address,
                                   string const& name) :
                                   _client(loop , address , name)
{
}

void ResGetFromRemote::applyResource(MessagePtr const& msg,
                                     TcpConnectionPtr const& conn)
{

}

void ResGetFromRemote::revokeResource(MessagePtr const& msg,
                                      TcpConnectionPtr const& conn)
{

}

void ResGetFromRemote::onApplyResourceACK(TcpConnectionPtr const& conn,
                                          MessagePtr const& msg,
                                          Timestamp timeStamp)
{

}

void ResGetFromRemote::onRevokeResourceACK(TcpConnectionPtr const& conn,
                                           MessagePtr const& msg,
                                           Timestamp timeStamp)
{

}