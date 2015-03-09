#include <DM/CustomizedServiceAcceptor.h>

CustomizedServiceAcceptor::~CustomizedServiceAcceptor()
{
}

/*
 * name : onPreserve
 *
 * description : the callback function which is used to preserve customized
 *               information for DC
 *
 * @conn : the connection of DC
 * @msg  : the preserve query from DC
 * @timeStamp : the receive timestamp of a query
 *
 * @return : none
 */
void CustomizedServiceAcceptor::onPreserve(muduo::net::TcpConnectionPtr const& conn,
                                           MessagePtr const& msg,
                                           muduo::Timestamp timeStamp)
{
}

/*
 * name : onLoad
 *
 * description : the callback function which is used to load/read customized
 *               information for DC
 *
 * @conn : the connection of DC
 * @msg  : the load/read query from DC
 * @timeStamp : the receive timestamp of a query
 *
 * @return : none
 */
void CustomizedServiceAcceptor::onLoad(muduo::net::TcpConnectionPtr const& conn,
                                       MessagePtr const& msg,
                                       muduo::Timestamp timeStamp)
{
}

/*
 * name : onDelete
 *
 * description : the callback function which is used to delete customized
 *               information for DC
 *
 * @conn : the connection of DC
 * @msg  : the delete query from DC
 * @timeStamp : the receive timestamp of a query
 *
 * @return : none
 */
void CustomizedServiceAcceptor::onDelete(muduo::net::TcpConnectionPtr const& conn,
                                         MessagePtr const& msg,
                                         muduo::Timestamp timeStamp)
{
}