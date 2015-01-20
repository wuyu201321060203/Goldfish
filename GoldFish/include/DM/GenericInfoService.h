#ifndef GENERICINFOSERVICE_H
#define GENERICINFOSERVICE_H

class GenericInfoService
{
public:

    virtual void onCreateInfo(TcpConnectionPtr const&,
                              MessagePtr const&,
                              muduo::Timestamp) = 0;

    virtual void onDeleteInfo(TcpConnectionPtr const&,
                              MessagePtr const&,
                              muduo::Timestamp) = 0;

    virtual void onUpdateInfo(TcpConnectionPtr const&,
                              MessagePtr const&,
                              muduo::Timestamp) = 0;

    virtual void onGetInfo(TcpConnectionPtr const&,
                           MessagePtr const&,
                           muduo::Timestamp) = 0;
};

#endif