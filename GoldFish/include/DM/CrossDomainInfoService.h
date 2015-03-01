#ifndef CROSSDOMAININFOSERVICE_H
#define CROSSDOMAININFOSERVICE_H

#include <vector>
#include <map>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>
#include <muduo/base/Types.h>

#include "Config.h"

class CrossDomainInfoService
{
public:

    virtual ~CrossDomainInfoService();

    typedef boost::function<void (TcpConnectionWeakPtrVec&)> DCListGetFunc;

    virtual void onCrossDomainInfoQuery(muduo::net::TcpConnectionPtr const&,
        MessagePtr const& , muduo::Timestamp) = 0;

    virtual void onCrossDomainInfoReplyFromDC(muduo::net::TcpConnectionPtr const&,
        MessagePtr const& , muduo::Timestamp) = 0;

    int setGetDCListFunc(DCListGetFunc const& func);

protected:

    class HelperFunctor
    {
    public:

        bool operator()(TcpConnectionWeakPtr conn);
    };

    TcpConnectionWeakPtrVec _dcVec;
    typedef std::map<muduo::string , TcpConnectionWeakPtr> Time2ConnMap;
    Time2ConnMap _cliMap;
    DCListGetFunc _func;
};

typedef boost::shared_ptr<CrossDomainInfoService> CrossDomainInfoServicePtr;

#endif