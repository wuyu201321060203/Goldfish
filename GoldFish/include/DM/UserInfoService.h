#ifndef USERINFOSERVICE_H
#define USERINFOSERVICE_H

#include <muduo/net/TcpConnection.h>

#include "GenericInfoService.h"
//#include "UserManager.h"
#include "Token.h"

class UserInfoService : public GenericInfoService
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

    void doCreateUser(muduo::net::TcpConnectionPtr const& , STDSTR , STDSTR,
                      STDSTR , STDSTR , ulong);

    void doDeleteUser(muduo::net::TcpConnectionPtr const& , STDSTR);

    void doUpdateUser(muduo::net::TcpConnectionPtr const& , STDSTR , STDSTR);

    void doGetUserInfo(muduo::net::TcpConnectionPtr const& , Token);
};

#endif