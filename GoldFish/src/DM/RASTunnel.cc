#include <DM/RASTunnel.h>

using namespace muduo;
using namespace muduo::net;


RASTunnel::RASTunnel(muduo::net::EventLoop* loop , muduo::net::InetAddress const& addr):
                    ResourceManager(loop , addr)
{
}

void RASTunnel::applyResource(MessagePtr const& msg,
                              muduo::net::TcpConnectionPtr const& cliConn)
{

}

void RASTunnel::revokeResource(MessagePtr const& msg,
                               muduo::net::TcpConnectionPtr const& cliConn)
{

}

void RASTunnel::onApplyResourceReply(muduo::net::TcpConnectionPtr const&,
                                     MessagePtr const&,
                                     muduo::Timestamp)
{

}

void RASTunnel::onRevokeResourceReply(muduo::net::TcpConnectionPtr const&,
                                      MessagePtr const&,
                                      muduo::Timestamp)
{

}