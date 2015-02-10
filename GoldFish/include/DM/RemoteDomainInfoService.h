#ifndef DOMAININFOSERVICE_H
#define DOMAININFOSERVICE_H

#include <boost/shared_ptr.hpp>

#include "GenericInfoService.h"
#include "ResourceManager.h"

typedef boost::shared_ptr<ResourceManager> ResourceManagerPtr;

class RemoteDomainInfoService : public GenericInfoService
{
public:

    RemoteDomainInfoService(ResourceManagerPtr const&);

    virtual void onCreateInfo(muduo::net::TcpConnectionPtr const&,
                              MessagePtr const&,
                              muduo::Timestamp);

    virtual void onDeleteInfo(muduo::net::TcpConnectionPtr const&,
                              MessagePtr const&,
                              muduo::Timestamp);

    virtual void onUpdateInfo(muduo::net::TcpConnectionPtr const&,
                              MessagePtr const&,
                              muduo::Timestamp);

    virtual void onGetInfo(muduo::net::TcpConnectionPtr const&,
                           MessagePtr const&,
                           muduo::Timestamp);

private:

    ResourceManagerPtr _manager;
};

#endif