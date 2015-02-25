#ifndef RASTUNNEL_H
#define RASTUNNEL_H

#include <vector>

#include <boost/shared_ptr.hpp>

#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpClient.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/base/Timestamp.h>

#include "ProtobufRASCodec.h"
#include "ResourceManager.h"
#include "Initializer.h"
#include "Config.h"
#include "HeartBeatManager.h"

typedef boost::shared_ptr<muduo::net::TcpClient> TcpClientPtr;

class RASTunnel : public ResourceManager
{
public:

    RASTunnel(muduo::net::EventLoop* , muduo::net::InetAddress const&);

    virtual void init();

    virtual void applyResource(STDSTR , STDSTR , double , uint32_t,
                               muduo::net::TcpConnectionPtr const&);

    virtual void revokeResource(uint32_t,
                                muduo::net::TcpConnectionPtr const&);

    void onApplyResourceReply(muduo::net::TcpConnectionPtr const&,
                              MessagePtr const&,
                              muduo::Timestamp);

    void onRevokeResourceReply(muduo::net::TcpConnectionPtr const&,
                               MessagePtr const&,
                               muduo::Timestamp);

#ifdef TEST
    muduo::net::TcpConnectionPtr getConn();
#endif

private:

    struct DomainInfoCache
    {
        std::string _domainName;
        std::string _domainDescription;
        double _cpuNum;
        uint32_t _cpuMemSize;
    };

private:

    muduo::net::TcpClient _rasMasterClient;
    std::vector<TcpConnectionWeakPtr> _cliConnApplyVec;
    std::vector<TcpConnectionWeakPtr> _cliConnRevokeVec;
    int _status;
    ProtobufRASCodec _rasCodec;
    std::vector<DomainInfoCache> _cacheVec;
    HeartBeatManager _hbManager;

private:

    void onConnectionCallbackFromRC(muduo::net::TcpConnectionPtr const&);
    void register2RAS(muduo::net::TcpConnectionPtr const&);

    void onRegisterCallback(muduo::net::TcpConnectionPtr const&,
                            MessagePtr const&,
                            muduo::Timestamp);

    void doCreateDomain(muduo::net::TcpConnectionPtr const& , uint32_t,
                        STDSTR , STDSTR , double , uint32_t);

    void doRevokeDomain(muduo::net::TcpConnectionPtr const& , uint32_t);

    template<typename T>
    void onFailSend(muduo::net::TcpConnectionPtr const& conn , int replyInfo)
    {
        T reply;
        reply.set_statuscode(replyInfo);
        (Initializer::getCodec()).send(conn , reply);
    }

    void onHeartBeat(muduo::net::TcpConnectionPtr const&,
                     MessagePtr const&,
                     muduo::Timestamp);

    void onTimeout(void);
};

#endif