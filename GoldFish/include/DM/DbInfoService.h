/*
 * DbInfoService is used to manage the cross-domain information about database
 */

#ifndef DBINFO_SERVICE_H
#define DBINFO_SERVICE_H

#include "CrossDomainInfoService.h"

class DbInfoService : public CrossDomainInfoService
{
public:

    DbInfoService(DMServer*);
    virtual void onCrossDomainInfoQuery(muduo::net::TcpConnectionPtr const&,
                                        MessagePtr const&,
                                        muduo::Timestamp);

    virtual void onCrossDomainInfoReplyFromDC(muduo::net::TcpConnectionPtr const&,
                                              MessagePtr const&,
                                              muduo::Timestamp);
#ifdef TEST
    Time2ConnMap& getCliMap();
#endif
};

#endif