#ifndef CUSTOMIZEDSERVICE_H
#define CUSTOMIZEDSERVICE_H

#include <muduo/base/Timestamp.h>

#include "Config.h"

class CustomizedServiceAcceptor
{
public:

    virtual void onPreserve(TcpConnectionPtr const& conn,
                            MessagePtr const& msg,
                            muduo::Timestamp timeStamp) = 0;

    virtual void onLoad(TcpConnectionPtr const& conn,
                        MessagePtr const& msg,
                        muduo::Timestamp timeStamp) = 0;

    virtual void onDelete(TcpConnectionPtr const& conn,
                        MessagePtr const& msg,
                        muduo::Timestamp timeStamp) = 0;
};

typedef boost::shared_ptr<CustomizedServiceAcceptor> CustomizedServiceAcceptorPtr;

#endif