/*
 *  The base class of DbInfoService and SysInfoService
 */

#ifndef CROSSDOMAININFOSERVICE_H
#define CROSSDOMAININFOSERVICE_H

#include <map>

#include <boost/shared_ptr.hpp>

#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>

#include "Config.h"

class DMServer;

class CrossDomainInfoService
{
public:

    CrossDomainInfoService(DMServer*);
    virtual ~CrossDomainInfoService();

    virtual void onCrossDomainInfoQuery(muduo::net::TcpConnectionPtr const&,
        MessagePtr const& , muduo::Timestamp) = 0;

    virtual void onCrossDomainInfoReplyFromDC(muduo::net::TcpConnectionPtr const&,
        MessagePtr const& , muduo::Timestamp) = 0;

    void addDCConn(muduo::net::TcpConnectionPtr const&);

protected:

    class HelperFunctor
    {
    public:

        bool operator()(TcpConnectionWeakPtr conn);
    };

    TcpConnectionWeakPtrVec _dcVec;
    typedef std::map<muduo::string , TcpConnectionWeakPtr> Time2ConnMap;
    Time2ConnMap _cliMap;
    DMServer* _dm;
};

typedef boost::shared_ptr<CrossDomainInfoService> CrossDomainInfoServicePtr;

#endif