#ifndef RASTUNNEL_H
#define RASTUNNEL_H

#include <vector>

#include <boost/shared_ptr.hpp>

#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpClient.h>
#include <muduo/base/Timestamp.h>

#include <DM/ProtobufRASCodec.h>

typedef boost::shared_ptr<muduo::net::TcpClient> TcpClientPtr;

#include "ReourceManager.h"

class RASTunnel : public ResourceManager
{
public:

    RASTunnel(muduo::net::EventLoop* , muduo::net::InetAddress const&);

    virtual void init();

    virtual void applyResource(STDSTR domainName , STDSTR domainDescription,
                       double cpuNum , uint32_t cpuMemSize,
                       muduo::net::TcpConnectionPtr const& cliConn);

    virtual void revokeResource(uint32_t domainID,
                                muduo::net::TcpConnectionPtr const& cliConn);

    void onApplyResourceReply(muduo::net::TcpConnectionPtr const&,
                              MessagePtr const&,
                              muduo::Timestamp);

    void onRevokeResourceReply(muduo::net::TcpConnectionPtr const&,
                               MessagePtr const&,
                               muduo::Timestamp);

private:

    struct DomainInfoCache
    {
        std::string _domainName;
        std::string _domainDescription;
        double _cpuNum;
        uint32_t _cpuMemSize;
        std::string _ip;
        uint32_t _port;
    };

private:

    muduo::net::TcpClient _rasMasterClient;
    std::vector<TcpConnectionWeakPtr> _cliConnApplyVec;
    std::vector<TcpConnectionWeakPtr> _cliConnRevokeVec;
    int _status;
    ProtobufRASCodec _rasCodec;
    std::vector<DomainInfoCache> _cacheVec;

private:

    void onConnectionCallbackFromRC(muduo::net::TcpConnectionPtr const&);
    void register2RAS(muduo::net::TcpConnectionPtr const&);

    void onRegisterCallback(muduo::net::TcpConnectionPtr const& conn,
                            MessagePtr const& msg,
                            muduo::Timestamp receiveTime);

    void doCreateDomain(muduo::net::TcpConnectionPtr const& conn , uint32_t domainID,
                        STDSTR domainName , STDSTR domainDescription,
                        double cpuNum , uint32_t cpuMemSize,
                        STDSTR IP , uint32_t port);

    void doRevokeDomain(muduo::net::TcpConnectionPtr const& conn , uint32_t domainID);

    template<typename T>
    void onFailSend(muduo::net::TcpConnectionPtr const& conn , T reply , int replyInfo)
    {
        T reply;
        reply.set_statuscode(replyInfo);
        (Initializer::getCodec()).send(conn , reply);
    }
};

#endif