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

void CrossDomainInfoService::gcCliConn(TcpConnectionPtr const& conn)
{
    for(Time2ConnMap::iterator i = _cliMap.begin() ; i != _cliMap.end() ; )
    {
        if(i->second->name() == conn->name())
            _cliMap.erase(i++);
        else
            ++i;
    }
}