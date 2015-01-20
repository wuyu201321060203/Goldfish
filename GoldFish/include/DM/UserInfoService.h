#ifndef USERINFOSERVICE_H
#define USERINFOSERVICE_H

#include "GenericInfoService.h"
#include "UserManager.h"

class USERInfoService : public GenericInfoService
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
};

#endif