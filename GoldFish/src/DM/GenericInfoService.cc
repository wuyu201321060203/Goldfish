#include <DM/GenericInfoService.h>

GenericInfoService::~GenericInfoService()
{
}

/*
 * name : onCreateInfo
 *
 * description : create record
 *
 * @conn : the connection of a client
 * @msg  : the query message from client
 * @receiveTime : the receive time of a query
 *
 * @return : none
 */
void GenericInfoService::onCreateInfo(muduo::net::TcpConnectionPtr const& conn,
                                      MessagePtr const& msg,
                                      muduo::Timestamp receiveTime)
{
}

/*
 * name : onDeleteInfo
 *
 * description : delete record
 *
 * @conn : the connection of a client
 * @msg  : the query message from client
 * @receiveTime : the receive time of a query
 *
 * @return : none
 */
void GenericInfoService::onDeleteInfo(muduo::net::TcpConnectionPtr const&,
                                      MessagePtr const&,
                                      muduo::Timestamp)
{
}

/*
 * name : onUpdateInfo
 *
 * description : update record
 *
 * @conn : the connection of a client
 * @msg  : the query message from client
 * @receiveTime : the receive time of a query
 *
 * @return : none
 */
void GenericInfoService::onUpdateInfo(muduo::net::TcpConnectionPtr const&,
                                      MessagePtr const&,
                                      muduo::Timestamp)
{
}

/*
 * name : onGetInfo
 *
 * description : get record
 *
 * @conn : the connection of a client
 * @msg  : the query message from client
 * @receiveTime : the receive time of a query
 *
 * @return : none
 */
void GenericInfoService::onGetInfo(muduo::net::TcpConnectionPtr const&,
                                   MessagePtr const&,
                                   muduo::Timestamp)
{
}