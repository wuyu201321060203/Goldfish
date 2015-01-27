#ifndef USERINFOSERVICE_H
#define USERINFOSERVICE_H

#include "GenericInfoService.h"
#include "UserManager.h"

class USERInfoService : public GenericInfoService
{
public:

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

    void doCreateUser(TcpConnectionPtr const& , STDSTR , STDSTR , STDSTR , STDSTR,
                                       ulong);

    void doDeleteUser(TcpConnectionPtr const& , STDSTR);

    void doUpdateUser(TcpConnectionPtr const& , STDSTR , STDSTR);

    void doGetUserInfo(TcpConnectionPtr const& , STDSTR);
};

#endif