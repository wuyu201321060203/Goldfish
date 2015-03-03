#include "gtest/gtest.h"

#include <DM/DbInfoService.h>
#include <DM/Config.h>
#include <DM/Initializer.h>
#include <DM/util.h>
#include <DM/Token.h>
#include <DM/DMServer.h>
#include <muduo/base/Types.h>
#include <boost/bind.hpp>
#include <map>
#include <string>
#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

std::map<muduo::string , DomainDbInfoGetMsg> testDbMap;
std::map<muduo::string , DomainDbInfoGetACK> testDbMap1;
TcpConnectionPtr dbconn1;
TcpConnectionPtr dbconn2;
std::string timeDb1;
typedef std::vector<TcpConnectionWeakPtr> TcpConnectionWeakPtrVec;
typedef std::map<muduo::string , TcpConnectionWeakPtr> Time2ConnMap;

TEST(DbInfoServiceTest , InfoQuerySuccessTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd1 = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    int socketfd2 = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    int socketfd3 = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    dbconn1.reset( new TcpConnection(&Initializer::getEventLoop(),
        "conn1" , socketfd1 , localAddr , remoteAddr) );
    dbconn2.reset( new TcpConnection(&Initializer::getEventLoop(),
        "conn2" , socketfd2 , localAddr , remoteAddr) );
    TcpConnectionPtr conn3(new TcpConnection(&Initializer::getEventLoop(),
                            "conn3" , socketfd3 , localAddr , remoteAddr));
    DMServer dm(&Initializer::getEventLoop() , Initializer::getOptions());
    DbInfoService waiter(&dm);
    waiter.addDCConn(dbconn1);
    waiter.addDCConn(dbconn2);
    STDSTR username("ddcnmb");
    STDSTR belong2Domain("domain1");
    STDSTR belong2Group("group1");
    unsigned int identity = 0b00000000;
    Token token(username , identity , belong2Domain , belong2Group);
    CrossDbInfoGetMsg* tmp =  new CrossDbInfoGetMsg;
    tmp->set_token(token.toString());
    MessagePtr msg(tmp);
    Timestamp time;
    waiter.onCrossDomainInfoQuery(conn3 , msg , time);
    DomainDbInfoGetMsg msg1 = testDbMap[dbconn1->name()];
    DomainDbInfoGetMsg msg2 = testDbMap[dbconn2->name()];
    EXPECT_EQ(timeDb1 , msg1.timestamp());
    EXPECT_EQ(timeDb1 , msg2.timestamp());
}

TEST(DbInfoServiceTest , InfoReplySuccessTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd1 = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    int socketfd2 = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    int socketfd3 = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    int socketfd4 = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    dbconn1.reset( new TcpConnection(&Initializer::getEventLoop(),
        "dcConn1" , socketfd1 , localAddr , remoteAddr) );
    dbconn2.reset( new TcpConnection(&Initializer::getEventLoop(),
        "dcConn2" , socketfd2 , localAddr , remoteAddr) );
    TcpConnectionPtr conn3(new TcpConnection(&Initializer::getEventLoop(),
                            "cliConn1" , socketfd3 , localAddr , remoteAddr));
    TcpConnectionPtr conn4(new TcpConnection(&Initializer::getEventLoop(),
                            "cliConn2" , socketfd4 , localAddr , remoteAddr));
    DMServer dm(&Initializer::getEventLoop() , Initializer::getOptions());
    DbInfoService waiter(&dm);
    waiter.addDCConn(dbconn1);
    waiter.addDCConn(dbconn2);
    STDSTR username("ddcnmb");
    STDSTR belong2Domain("domain1");
    STDSTR belong2Group("group1");
    unsigned int identity = 0b00000000;
    Token token(username , identity , belong2Domain , belong2Group);
    CrossDbInfoGetMsg* tmp =  new CrossDbInfoGetMsg;
    tmp->set_token(token.toString());
    MessagePtr msg(tmp);
    Timestamp time;
    waiter.onCrossDomainInfoQuery(conn3 , msg , time);
    std::string timeConn3 = timeDb1;
    sleep(3);
    waiter.onCrossDomainInfoQuery(conn4 , msg , time);
    std::string timeConn4 = timeDb1;
    Time2ConnMap& clients = waiter.getCliMap();
    TcpConnectionPtr cli1 = clients[StdStr2MuduoStr(timeConn3)].lock();
    TcpConnectionPtr cli2 = clients[StdStr2MuduoStr(timeConn4)].lock();
    muduo::string cli1Name = cli1->name();
    muduo::string cli2Name = cli2->name();
    EXPECT_EQ(conn3->name() , cli1Name);
    EXPECT_EQ(conn4->name() , cli2Name);
    DomainDbInfoGetACK* ackMsg = new DomainDbInfoGetACK;
    ackMsg->set_timestamp(timeConn3);
    MessagePtr msg1(ackMsg);
    waiter.onCrossDomainInfoReplyFromDC(dbconn1 , msg1 , time);
    EXPECT_EQ(ackMsg->timestamp() , (testDbMap1[conn3->name()]).timestamp());
}