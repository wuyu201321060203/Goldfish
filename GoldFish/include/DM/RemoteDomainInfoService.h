#ifndef DOMAININFOSERVICE_H
#define DOMAININFOSERVICE_H

#include <boost/shared_ptr.hpp>

#include "GenericInfoService.h"

typedef boost::shared_ptr<ResourceManager> ResourceManagerPtr;

class RemoteDomainInfoService : public GenericInfoService
{
public:

    RemoteDomainInfoService(ResourceManagerPtr const&);
    virtual void onCreateInfo(TcpConnectionPtr const&,
                              MessagePtr const&,
                              muduo::Timestamp);

    virtual void onDeleteInfo(TcpConnectionPtr const&,
                              MessagePtr const&,
                              muduo::Timestamp);

    virtual void onUpdateInfo(TcpConnectionPtr const&,
                              MessagePtr const&,
                              muduo::Timestamp);

    virtual void onGetInfo(TcpConnectionPtr const&,
                           MessagePtr const&,
                           muduo::Timestamp);

private:

    ResourceManagerPtr _manager;
};

#endif