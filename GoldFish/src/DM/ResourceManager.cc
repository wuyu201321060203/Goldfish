#include <DM/ResourceManager.h>
#include <DM/Initializer.h>

using namespace muduo;
using namespace muduo::net;

ResourceManager::ResourceManager(EventLoop* loop , InetAddress const& addr)
                            :_rasMasterClient(loop , addr , "RASClient")
{

}

void ResourceManager::applyResource(MessagePtr const& msg,
                                    TcpConnectionPtr const& cliConn)
{
}

void ResourceManager::revokeResource(MessagePtr const& msg,
                                     TcpConnectionPtr const& cliConn)
{
}

void ResourceManager::onApplyResourceReply(TcpConnectionPtr const& conn,
                                           MessagePtr const& msg,
                                           Timestamp time)
{
}

void ResourceManager::onRevokeResourceReply(TcpConnectionPtr const& conn,
                                            MessagePtr const& msg,
                                            Timestamp time)
{
}