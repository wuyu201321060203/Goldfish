#ifndef SYSINFO_SERVICE_H
#define SYSINFO_SERVICE_H

#include <muduo/net/TcpConnection.h>

#include "CrossDomainInfoService.h"

class SysInfoService : public CrossDomainInfoService
{
public:

    void onSysInfoQuery(TcpConnectionPtr const&,
                        SysInfoMsgPtr const&,
                        muduo::Timestamp);

    void onSysInfoReplyFromDC(TcpConnectionPtr const&,
                              SysInfoReplyPtr const&,
                              muduo::Timestamp);
};

#endif