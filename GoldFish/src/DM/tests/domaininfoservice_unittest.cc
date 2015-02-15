#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <unistd.h>

#include <muduo/base/Types.h>

#include <DM/Config.h>
#include <DM/util.h>
#include <DM/RemoteDomainInfoService.h>
#include <DM/RASTunnel.h>
#include <Db/ConnectionPool.h>
#include <Db/ResultSet.h>
#include <Db/Connection.h>
#include <DM/Token.h>
#include <mysql/MysqlConnection.h>

#include <boost/shared_ptr.hpp>

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;

typedef boost::shared_ptr<MutexLock> MutexLockPtr;
extern MutexLockPtr mutex;

std::vector<MSG_DM_CLIENT_DOMAIN_DESCRIPTION_GET_ACK_DOMAIN_INFO> testDomainArray;

TEST(DomainInfoServiceTest , UpdateInfoSuccessTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn( new TcpConnection(&g_Initializer.getEventLoop(),
                                "conn" , socketfd , localAddr , remoteAddr) );
    conn->setContext(mutex);
    STDSTR username("ddcnmb");
    STDSTR userBelong2Domain("*");
    STDSTR userBelong2Group("*");
    unsigned int identity = 0b00000000;
    Token token(username , identity , userBelong2Domain , userBelong2Group);
    DomainInfoUpdateMsg* tmp =  new DomainInfoUpdateMsg;
    tmp->set_token(token.toString());
    tmp->set_domainname("domain1");
    tmp->set_domaindescription("OK");
    MessagePtr msg(tmp);
    Timestamp time;
    boost::shared_ptr<ResourceManager> manager(new RASTunnel(
                        &g_Initializer.getEventLoop() , localAddr));
    RemoteDomainInfoService waiter(manager);
    waiter.onUpdateInfo(conn , msg , time);
    sleep(3);
    ConnectionPtr dbConn = Initializer::getDbPool().getConnection<MysqlConnection>();
    ResultSetPtr result = dbConn->executeQuery("select description from DOMAIN_INFO where name = 'domain1'");
    STDSTR testDes;
    if(result->next())
    {
        testDes = result->getString(1);
    }
    EXPECT_EQ("OK" , testDes);
}

TEST(DomainInfoServiceTest , GetSingleInfoSuccessTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn( new TcpConnection(&g_Initializer.getEventLoop(),
                                "conn" , socketfd , localAddr , remoteAddr) );
    conn->setContext(mutex);
    STDSTR username("ddcnmb");
    STDSTR userBelong2Domain("domain1");
    STDSTR userBelong2Group("group1");
    unsigned int identity = 0b00001000;
    Token token(username , identity , userBelong2Domain , userBelong2Group);
    DomainInfoGetMsg* tmp =  new DomainInfoGetMsg;
    tmp->set_token(token.toString());
    MessagePtr msg(tmp);
    Timestamp time;
    boost::shared_ptr<ResourceManager> manager(new RASTunnel(
                        &g_Initializer.getEventLoop() , localAddr));
    RemoteDomainInfoService waiter(manager);
    waiter.onGetInfo(conn , msg , time);
    sleep(3);
    EXPECT_EQ("domain1" , testDomainArray[0].name());
    EXPECT_EQ("OK" , testDomainArray[0].description());
}

/*
TEST(DomainInfoServiceTest , GetNoSingleInfoSuccessTest)
{
    testArray.clear();
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn( new TcpConnection(&g_Initializer.getEventLoop(),
                                "conn" , socketfd , localAddr , remoteAddr) );
    conn->setContext(mutex);
    STDSTR username("ddcnmb");
    STDSTR userBelong2Domain("domain1");
    STDSTR userBelong2Group("*");
    unsigned int identity = 0b00001000;
    Token token(username , identity , userBelong2Domain , userBelong2Group);
    GroupInfoGetMsg* tmp =  new GroupInfoGetMsg;
    tmp->set_token(token.toString());
    MessagePtr msg(tmp);
    Timestamp time;
    GroupInfoService waiter;
    waiter.onGetInfo(conn , msg , time);
    sleep(3);
    EXPECT_EQ("group1" , testArray[0].name());
    EXPECT_EQ("group1" , testArray[0].description());
    EXPECT_EQ("group2" , testArray[1].name());
    EXPECT_EQ("group2new" , testArray[1].description());
}
*/