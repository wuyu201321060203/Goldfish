#ifndef DBINFO_SERVICE_H
#define DBINFO_SERVICE_H

#include <muduo/net/TcpConnection.h>

#include "CrossDomainInfoService.h"

class DbInfoService : public CrossDomainInfoService
{
public:

    virtual void onCrossDomainInfoQuery(TcpConnectionPtr const&,
                                        MessagePtr const&,
                                        muduo::Timestamp);

    virtual void onCrossDomainInfoReplyFromDC(TcpConnectionPtr const&,
                                              MessagePtr const&,
                                              muduo::Timestamp);
};

#endif