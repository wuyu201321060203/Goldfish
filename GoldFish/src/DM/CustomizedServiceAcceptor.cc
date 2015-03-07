#include <DM/CustomizedServiceAcceptor.h>

CustomizedServiceAcceptor::~CustomizedServiceAcceptor()
{
}

void CustomizedServiceAcceptor::onPreserve(muduo::net::TcpConnectionPtr const& conn,
                                           MessagePtr const& msg,
                                           muduo::Timestamp timeStamp)
{
}

void CustomizedServiceAcceptor::onLoad(muduo::net::TcpConnectionPtr const& conn,
                                       MessagePtr const& msg,
                                       muduo::Timestamp timeStamp)
{
}

void CustomizedServiceAcceptor::onDelete(muduo::net::TcpConnectionPtr const& conn,
                                         MessagePtr const& msg,
                                         muduo::Timestamp timeStamp)
{
}