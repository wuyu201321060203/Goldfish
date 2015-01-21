#ifndef CUSTOMIZEDSERVICE_H
#define CUSTOMIZEDSERVICE_H

#include <muduo/base/Timestamp.h>

#include "Config.h"

class CustomizedServiceAcceptor
{
public:

    virtual void onPreserve(muduo::net::TcpConnectionPtr const& conn,
                            MessagePtr const& msg,
                            muduo::Timestamp timeStamp) = 0;

    virtual void onLoad(muduo::net::TcpConnectionPtr const& conn,
                        MessagePtr const& msg,
                        muduo::Timestamp timeStamp) = 0;

    virtual void onDelete(muduo::net::TcpConnectionPtr const& conn,
                          MessagePtr const& msg,
                          muduo::Timestamp timeStamp) = 0;
};

typedef boost::shared_ptr<CustomizedServiceAcceptor> CustomizedServiceAcceptorPtr;

#endif