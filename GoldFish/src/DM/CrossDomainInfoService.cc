#include <DM/CrossDomainInfoService.h>

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

int CrossDomainInfoService::setGetDCListFunc(DCListGetFunc const& func)
{
    _func = func;
    return RET_SUCCESS;
}

bool CrossDomainInfoService::HelperFunctor::operator()(TcpConnectionWeakPtr conn)
{
    muduo::net::TcpConnectionPtr tmp( conn.lock() );
    return tmp ? true : false;
}