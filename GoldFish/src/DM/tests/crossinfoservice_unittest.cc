#include "gtest/gtest.h"

#include <DM/CrossInfoService.h>
#include <DM/Config.h>
#include <DM/util.h>
#include <muduo/base/Types.h>
#include <boost/bind.hpp>
#include <map>
#include <string>

std::map<muduo::string , DomainDbInfoGetMsg> testMap;
std::map<muduo::string , DomainDbInfoGetACK> testMap1;
TcpConnectionPtr conn1;
TcpConnectionPtr conn2;
std::string time1;
typedef std::vector<TcpConnectionWeakPtr> TcpConnectionWeakPtrVec;
typedef std::map<muduo::string , TcpConnectionWeakPtr> Time2ConnMap;

using namespace muduo;
using namespace muduo::net;

static void dcGetTestFunc(TcpConnectionWeakPtrVec& vec)
{
    vec.push_back(conn1);
    vec.push_back(conn2);
}

TEST(CrossInfoServiceTest , InfoQuerySuccessTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd1 = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    int socketfd2 = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    int socketfd3 = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    conn1.reset( new TcpConnection(&g_Initializer.getEventLoop(),
        "conn1" , socketfd1 , localAddr , remoteAddr) );
    conn2.reset( new TcpConnection(&g_Initializer.getEventLoop(),
        "conn2" , socketfd2 , localAddr , remoteAddr) );
    TcpConnectionPtr conn3(new TcpConnection(&g_Initializer.getEventLoop(),
                            "conn3" , socketfd3 , localAddr , remoteAddr));
    CrossInfoService<CrossDbInfoGetMsg , CrossDbInfoGetACK,
                     DomainDbInfoGetMsg , DomainDbInfoGetACK> waiter;
    waiter.setGetDCListFunc(boost::bind(&dcGetTestFunc , _1));
    STDSTR username("ddcnmb");
    STDSTR belong2Domain("domain1");
    STDSTR belong2Group("group1");
    unsigned int identity = 0b00000000;
    Token token(username , identity , belong2Domain , belong2Group);
    CrossDbInfoGetMsg* tmp =  new CrossDbInfoGetMsg;
    tmp->set_token(token.toString());
    MessagePtr msg(tmp);
    Timestamp time;
    waiter.onCrossInfoQuery(conn3 , msg , time);
    DomainDbInfoGetMsg msg1 = testMap[conn1->name()];
    DomainDbInfoGetMsg msg2 = testMap[conn2->name()];
    EXPECT_EQ(time1 , msg1.timestamp());
    EXPECT_EQ(time1 , msg2.timestamp());
}

TEST(CrossInfoServiceTest , InfoReplySuccessTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd1 = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    int socketfd2 = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    int socketfd3 = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    int socketfd4 = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    conn1.reset( new TcpConnection(&g_Initializer.getEventLoop(),
        "dcConn1" , socketfd1 , localAddr , remoteAddr) );
    conn2.reset( new TcpConnection(&g_Initializer.getEventLoop(),
        "dcConn2" , socketfd2 , localAddr , remoteAddr) );
    TcpConnectionPtr conn3(new TcpConnection(&g_Initializer.getEventLoop(),
                            "cliConn1" , socketfd3 , localAddr , remoteAddr));
    TcpConnectionPtr conn4(new TcpConnection(&g_Initializer.getEventLoop(),
                            "cliConn2" , socketfd4 , localAddr , remoteAddr));
    CrossInfoService<CrossDbInfoGetMsg , CrossDbInfoGetACK,
                     DomainDbInfoGetMsg , DomainDbInfoGetACK> waiter;
    waiter.setGetDCListFunc(boost::bind(&dcGetTestFunc , _1));
    STDSTR username("ddcnmb");
    STDSTR belong2Domain("domain1");
    STDSTR belong2Group("group1");
    unsigned int identity = 0b00000000;
    Token token(username , identity , belong2Domain , belong2Group);
    CrossDbInfoGetMsg* tmp =  new CrossDbInfoGetMsg;
    tmp->set_token(token.toString());
    MessagePtr msg(tmp);
    Timestamp time;
    waiter.onCrossInfoQuery(conn3 , msg , time);
    std::string timeConn3 = time1;
    waiter.onCrossInfoQuery(conn4 , msg , time);
    std::string timeConn4 = time1;
    Time2ConnMap& clients = waiter.getCliMap();
    TcpConnectionPtr cli1 = clients[StdStr2MuduoStr(timeConn3)].lock();
    TcpConnectionPtr cli2 = clients[StdStr2MuduoStr(timeConn4)].lock();
    EXPECT_EQ(conn3->name() , cli1->name());
    EXPECT_EQ(conn4->name() , cli2->name());
    DomainDbInfoGetACK* ackMsg = new DomainDbInfoGetACK;
    ackMsg->set_timestamp(timeConn3);
    MessagePtr msg1(ackMsg);
    waiter.onCrossInfoReplyFromDC(conn1 , msg1 , time);
    EXPECT_EQ(ackMsg->timestamp() , (testMap1[conn3->name()]).timestamp());
}