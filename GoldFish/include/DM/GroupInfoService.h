#ifndef GROUPINFOSERVICE_H
#define GROUPINFOSERVICE_H

#include "GenericInfoService.h"

class GroupInfoService : public GenericInfoService
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
private:

    void doCreateGroup(TcpConnectionPtr const& , string , string , string);
    void doDeleteGroup(TcpConnectionPtr const& , string);
    void doUpdateGroup(TcpConnectionPtr const& , string , string);
    void doGetGroup(TcpConnectionPtr const& , string);
};

#endif