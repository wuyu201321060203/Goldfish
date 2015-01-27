#ifndef GROUPINFOSERVICE_H
#define GROUPINFOSERVICE_H

#include <string>

#include "GenericInfoService.h"
#include "Initializer.h"

extern Initializer g_Initializer;

class GroupInfoService : public GenericInfoService
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

    void doCreateGroup(muduo::net::TcpConnectionPtr const& , std::string,
                       std::string , std::string);
    void doDeleteGroup(muduo::net::TcpConnectionPtr const& , std::string);
    void doUpdateGroup(muduo::net::TcpConnectionPtr const& , std::string,
                       std::string);
    void doGetGroup(muduo::net::TcpConnectionPtr const& , std::string);

    template<typename T>
    void onTokenFailAuthFailed(muduo::net::TcpConnectionPtr const& conn)
    {
        T reply;
        reply.set_statuscode(PERMISSION_DENIED);
        ( g_Initializer.getCodec()  ).send(conn , reply);
    }
};

#endif