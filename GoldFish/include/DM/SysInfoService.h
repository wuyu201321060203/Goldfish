#ifndef SYSINFO_SERVICE_H
#define SYSINFO_SERVICE_H

#include <muduo/net/TcpConnection.h>

#include "CrossDomainInfoService.h"

class SysInfoService : public CrossDomainInfoService
{
public:

    void onSysInfoQuery(muduo::net::TcpConnectionPtr const&,
                        MessagePtr const&,
                        muduo::Timestamp);

    void onSysInfoReplyFromDC(muduo::net::TcpConnectionPtr const&,
                              MessagePtr const&,
                              muduo::Timestamp);
};

#endif