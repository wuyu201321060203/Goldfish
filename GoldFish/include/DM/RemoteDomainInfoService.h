#ifndef DOMAININFOSERVICE_H
#define DOMAININFOSERVICE_H

#include "GenericInfoService.h"

class RemoteDomainInfoService : public GenericInfoService
{
public:

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

    ResManagerPtr getResManager();

private:

    ResManagerPtr _resManager;
};

#endif