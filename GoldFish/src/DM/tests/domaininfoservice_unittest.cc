#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <unistd.h>

#include <muduo/base/Types.h>

#include <DM/Config.h>
#include <DM/util.h>
#include <DM/RemoteDomainInfoService.h>
#include <Db/ConnectionPool.h>
#include <Db/ResultSet.h>
#include <Db/Connection.h>
#include <DM/Token.h>
#include <mysql/MysqlConnection.h>

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;

typedef boost::shared_ptr<MutexLock> MutexLockPtr;
extern MutexLockPtr mutex;

TEST(DomainInfoServiceTest , UpdateInfoSuccessTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn( new TcpConnection(&g_Initializer.getEventLoop(),
                                "conn" , socketfd , localAddr , remoteAddr) );
    conn->setContext(mutex);
    STDSTR groupName("group2");
    STDSTR description("group2new");
    STDSTR username("ddcnmb");
    STDSTR userBelong2Domain("*");
    STDSTR userBelong2Group("*");
    unsigned int identity = 0b00000000;
    Token token(username , identity , userBelong2Domain , userBelong2Group);
    GroupInfoUpdateMsg* tmp =  new GroupInfoUpdateMsg;
    tmp->set_token(token.toString());
    tmp->set_groupname(groupName);
    tmp->set_groupdescription(description);
    MessagePtr msg(tmp);
    Timestamp time;
    GroupInfoService waiter;
    waiter.onUpdateInfo(conn , msg , time);
    sleep(3);
    ConnectionPtr dbConn = Initializer::getDbPool().getConnection<MysqlConnection>();
    ResultSetPtr result = dbConn->executeQuery("select description , belong2Domain\
                            from GROUP_INFO where name = 'group2'");
    STDSTR testDes;
    int testbelong2Domain;
    if(result->next())
    {
        testDes = result->getString(1);
        testbelong2Domain = result->getInt(2);
    }
    EXPECT_EQ("group2new" , testDes);
    EXPECT_EQ(1 , testbelong2Domain);
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
    GroupInfoGetMsg* tmp =  new GroupInfoGetMsg;
    tmp->set_token(token.toString());
    MessagePtr msg(tmp);
    Timestamp time;
    GroupInfoService waiter;
    waiter.onGetInfo(conn , msg , time);
    sleep(3);
    EXPECT_EQ("group1" , testArray[0].name());
    EXPECT_EQ("group1" , testArray[0].description());
}

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