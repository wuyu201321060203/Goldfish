#include <DM/CrossDomainInfoService.h>

CrossDomainInfoService::CrossDomainInfoService(DMServer* dm):_dm(dm)
{

}

CrossDomainInfoService::~CrossDomainInfoService()
{
}

void CrossDomainInfoService::onCrossDomainInfoQuery(muduo::net::TcpConnectionPtr const&,
                                                    MessagePtr const&,
                                                    muduo::Timestamp)
{
}

void CrossDomainInfoService::onCrossDomainInfoReplyFromDC(muduo::net::TcpConnectionPtr const&,
                                                          MessagePtr const&,
                                                          muduo::Timestamp)
{
}

void CrossDomainInfoService::addDCConn(muduo::net::TcpConnectionPtr const& conn)
{
    _dcVec.push_back(conn);
}

bool CrossDomainInfoService::HelperFunctor::operator()(TcpConnectionWeakPtr conn)
{
    muduo::net::TcpConnectionPtr tmp( conn.lock() );
    return tmp ? false : true;
}