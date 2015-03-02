#ifndef DCREGISTER_H
#define DCREGISTER_H

#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>

#include <DM/Config.h>

class DCRegister
{
public:

    DCRegister();

    void onMessage(muduo::net::TcpConnectionPtr const& conn,
                   MessagePtr const& msg,
                   muduo::Timestamp receiveTime);

private:

    void doRegister(muduo::net::TcpConnectionPtr const& conn,
                    uint32_t moduleID , STDSTR ip , uint32_t port);
};

#endif