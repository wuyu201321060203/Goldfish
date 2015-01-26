#ifndef GENERICINFOSERVICE_H
#define GENERICINFOSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>

#include "Config.h"

class GenericInfoService
{
public:

    virtual void onCreateInfo(muduo::net::TcpConnectionPtr const&,
                              MessagePtr const&,
                              muduo::Timestamp) = 0;

    virtual void onDeleteInfo(muduo::net::TcpConnectionPtr const&,
                              MessagePtr const&,
                              muduo::Timestamp) = 0;

    virtual void onUpdateInfo(muduo::net::TcpConnectionPtr const&,
                              MessagePtr const&,
                              muduo::Timestamp) = 0;

    virtual void onGetInfo(muduo::net::TcpConnectionPtr const&,
                           MessagePtr const&,
                           muduo::Timestamp) = 0;
};

#endif