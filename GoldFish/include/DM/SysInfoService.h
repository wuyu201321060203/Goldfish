#ifndef SYSINFO_SERVICE_H
#define SYSINFO_SERVICE_H

#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>

#include "CrossDomainInfoService.h"

class SysInfoService : public CrossDomainInfoService
{
public:

    SysInfoService();

    virtual void onCrossDomainInfoQuery(muduo::net::TcpConnectionPtr const&,
                                        MessagePtr const&,
                                        muduo::Timestamp);

    virtual void onCrossDomainInfoReplyFromDC(muduo::net::TcpConnectionPtr const&,
                                              MessagePtr const&,
                                              muduo::Timestamp);
};

#endif