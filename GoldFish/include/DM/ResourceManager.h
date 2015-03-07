#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <boost/shared_ptr.hpp>

#include <muduo/net/TcpConnection.h>

#include "Config.h"

class ResourceManager
{
public:

    virtual ~ResourceManager();
    virtual void init();

    virtual void applyResource(STDSTR , STDSTR , double , uint32_t,
                               muduo::net::TcpConnectionPtr const&) = 0;

    virtual void revokeResource(uint32_t,
                                muduo::net::TcpConnectionPtr const&) = 0;
};

typedef boost::shared_ptr<ResourceManager> ResourceManagerPtr;

#endif