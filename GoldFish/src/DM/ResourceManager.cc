#include <DM/ResourceManager.h>

using namespace muduo;
using namespace muduo::net;

void ResourceManager::init()
{
}

void ResourceManager::applyResource(STDSTR domainName,
                                    STDSTR description,
                                    double coreNum,
                                    uint32_t memSize,
                                    TcpConnectionPtr const& cliConn)
{
}

void ResourceManager::revokeResource(uint32_t domainID,
                                     TcpConnectionPtr const& cliConn)
{
}