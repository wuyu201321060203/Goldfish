#ifndef DBACCEPTOR_H
#define DBACCEPTOR_H

#include "CustomizedServiceAcceptor.h"

class DbAcceptor : public CustomizedServiceAcceptor
{
public:

    DbAcceptor();

    void onPreserve(muduo::net::TcpConnectionPtr const& conn,
                    MessagePtr const& msg,
                    muduo::Timestamp timeStamp);

    void onLoad(muduo::net::TcpConnectionPtr const& conn,
                MessagePtr const& msg,
                muduo::Timestamp timeStamp);

    void onDelete(muduo::net::TcpConnectionPtr const& conn,
                  MessagePtr const& msg,
                  muduo::Timestamp timeStamp);
private:

    void doPreserve(muduo::net::TcpConnectionPtr const& conn,
                    MessagePtr const& msg,
                    muduo::Timestamp timeStamp);

    void doLoad(muduo::net::TcpConnectionPtr const& conn,
                MessagePtr const& msg,
                muduo::Timestamp timeStamp);

    void doDelete(muduo::net::TcpConnectionPtr const& conn,
                  MessagePtr const& msg,
                  muduo::Timestamp timeStamp);
};

#endif