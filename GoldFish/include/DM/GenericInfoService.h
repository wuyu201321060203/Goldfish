#ifndef GENERICINFOSERVICE_H
#define GENERICINFOSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>

#include "Config.h"
#include "Initializer.h"

#ifdef TEST
extern GroupCreateACK testReply;
#endif

extern Initializer g_Initializer;

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

protected:

    template<typename T>
    void onTokenFailAuthFailed(muduo::net::TcpConnectionPtr const& conn)
    {
        T reply;
        reply.set_statuscode(PERMISSION_DENIED);
#ifndef TEST
        ( g_Initializer.getCodec()  ).send(conn , reply);
#else
        testReply.set_statuscode(reply.statuscode());
#endif
    }
};

#endif