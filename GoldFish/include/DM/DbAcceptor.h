#ifndef DBACCEPTOR_H
#define DBACCEPTOR_H

#include "CustomizedServiceAcceptor.h"

class DbAcceptor : public CustomizedServiceAcceptor
{
public:

    void onPreserve(TcpConnectionPtr const& conn,
                    MessagePtr const& msg,
                    muduo::Timestamp timeStamp);

    void onLoad(TcpConnectionPtr const& conn,
                MessagePtr const& msg,
                muduo::Timestamp timeStamp);

    void onDelete(TcpConnectionPtr const& conn,
                MessagePtr const& msg,
                muduo::Timestamp timeStamp);
};

#endif