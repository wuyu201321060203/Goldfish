#include <DM/CrossDomainInfoService.h>

CrossDomainInfoService::CrossDomainInfoService(DMServer* dm):_dm(dm)
{

}

CrossDomainInfoService::~CrossDomainInfoService()
{
}

/*
 * name : onCrossDomainInfoQuery
 *
 * description : The callback function which is called to deal with the query for
 *               cross-domain information from client.
 *
 * @conn : the smart ptr of connection of client who queries
 * @msg  : the query message
 * @receiveTime : the receive time of query
 *
 * @return : none
 */
void CrossDomainInfoService::onCrossDomainInfoQuery(
                                        muduo::net::TcpConnectionPtr const& conn,
                                        MessagePtr const& msg,
                                        muduo::Timestamp receiveTime)
{
}

/*
 * name : onCrossDomainInfoReplyFromDC
 *
 * description : the callback function called when there is reply from some DC
 *
 * @conn : the connection of DC
 * @msg  : the reply from DC
 * @receiveTime : the receive time of the reply
 *
 * @return : none
 */
void CrossDomainInfoService::onCrossDomainInfoReplyFromDC(
                                        muduo::net::TcpConnectionPtr const& conn,
                                        MessagePtr const& msg,
                                        muduo::Timestamp receiveTime)
{
}

/*
 * name : addDCConn
 *
 * description : This function is called by the doRegister interface of DCRegister
 *               class. And it help all the classes inherited from this class
 *               determine how many DC at the time.
 *
 * @conn : the smart ptr of connection of DC
 *
 * @return : none
 */
void CrossDomainInfoService::addDCConn(muduo::net::TcpConnectionPtr const& conn)
{
    _dcVec.push_back(conn);
}

/*
 * name : operator()
 *
 * description : The assist function for all the classes inherited from this
 *               class. It help them determine if DC is alive(connected) now.
 *
 * @conn: The weak ptr of connection of DC
 *
 * @return : true if DC is disconnected or false if DC is connected.
 */
bool CrossDomainInfoService::HelperFunctor::operator()(TcpConnectionWeakPtr conn)
{
    muduo::net::TcpConnectionPtr tmp( conn.lock() );
    return tmp ? false : true;
}