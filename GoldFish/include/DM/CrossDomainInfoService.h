#ifndef CROSSDOMAININFOSERVICE_H
#define CROSSDOMAININFOSERVICE_H

#include <vector>
#include <map>

#include <boost/function.hpp>

#include <muduo/base/Timestamp.h>

#include "Config.h"

class CrossDomainInfoService
{
public:

    typedef std::vector<TcpConnectionWeakPtr> TcpConnectionWeakPtrVec;
    typedef boost::function<void (TcpConnectionWeakPtrVec&)> DCListGetFunc;

    virtual void onCrossDomainInfoQuery(TcpConnectionPtr const& , MessagePtr const&,
                                muduo::Timestamp) = 0;

    virtual void onCrossDomainInfoReplyFromDC(TcpConnectionPtr const& , MessagePtr const&,
                                      muduo::Timestamp) = 0;

    int setGetDCListFunc(DCListGetFunc const& func);
    void gcCliConn(TcpConnectionPtr const&);

protected:

    TcpConnectionWeakPtrVec _dcVec;
    typedef std::map<muduo::Timestamp , TcpConnectionWeakPtr> Time2ConnMap;
    Time2ConnMap _cliMap;
    DCListGetFunc _func;
};

#endif