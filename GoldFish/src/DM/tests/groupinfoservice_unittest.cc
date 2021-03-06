#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <unistd.h>

#include <muduo/base/Types.h>

#include <DM/Config.h>
#include <DM/util.h>
#include <DM/GroupInfoService.h>
#include <Db/ConnectionPool.h>
#include <Db/ResultSet.h>
#include <Db/Connection.h>
#include <DM/Token.h>
#include <mysql/MysqlConnection.h>

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;

//extern ConnectionPool Initializer::getDbPool();
typedef boost::shared_ptr<MutexLock> MutexLockPtr;
extern MutexLockPtr mutex;

GroupCreateACK testReply;

typedef MSG_DM_CLIENT_GROUP_DESCRIPTION_GET_ACK_GROUP_INFO GroupInfoType;
std::vector<GroupInfoType> testArray;

TEST(GroupInfoServiceTest , CreateInfoSuccessTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn( new TcpConnection(&g_Initializer.getEventLoop(),
                                "conn" , socketfd , localAddr , remoteAddr) );
    conn->setContext(mutex);
    STDSTR belong2Domain("domain1");
    STDSTR groupName("group2");
    STDSTR description("group2");
    STDSTR username("ddcnmb");
    STDSTR userBelong2Domain("*");
    STDSTR userBelong2Group("*");
    unsigned int identity = 0b00000000;
    Token token(username , identity , userBelong2Domain , userBelong2Group);
    GroupCreateMsg* tmp =  new GroupCreateMsg;
    tmp->set_token(token.toString());
    tmp->set_groupname(groupName);
    tmp->set_belong2domain(belong2Domain);
    tmp->set_groupdescription(description);
    MessagePtr msg(tmp);
    Timestamp time;
    GroupInfoService waiter;
    waiter.onCreateInfo(conn , msg , time);
    sleep(3);
    ConnectionPtr dbConn = Initializer::getDbPool().getConnection<MysqlConnection>();
    ResultSetPtr result = dbConn->executeQuery("select description , belong2Domain\
                            from GROUP_INFO where name = 'group2'");
    sleep(3);
    STDSTR testDes;
    int testbelong2Domain;
    if(result->next())
    {
        testDes = result->getString(1);
        testbelong2Domain = result->getInt(2);
    }
    EXPECT_EQ("group2" , testDes);
    EXPECT_EQ(1 , testbelong2Domain);
}

TEST(GroupInfoServiceTest , CreateInfoFailTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn( new TcpConnection(&g_Initializer.getEventLoop(),
                                "conn" , socketfd , localAddr , remoteAddr) );
    conn->setContext(mutex);
    STDSTR belong2Domain("domain1");
    STDSTR groupName("group2");
    STDSTR description("group2");
    STDSTR username("ddcnmb");
    STDSTR userBelong2Domain("*");
    STDSTR userBelong2Group("*");
    unsigned int identity = 0b00001000;
    Token token(username , identity , userBelong2Domain , userBelong2Group);
    GroupCreateMsg* tmp =  new GroupCreateMsg;
    tmp->set_token(token.toString());
    tmp->set_groupname(groupName);
    tmp->set_belong2domain(belong2Domain);
    tmp->set_groupdescription(description);
    MessagePtr msg(tmp);
    Timestamp time;
    GroupInfoService waiter;
    waiter.onCreateInfo(conn , msg , time);
    EXPECT_EQ(PERMISSION_DENIED , testReply.statuscode());
}

TEST(GroupInfoServiceTest , UpdateInfoSuccessTest)
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

TEST(GroupInfoServiceTest , GetSingleInfoSuccessTest)
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

TEST(GroupInfoServiceTest , GetNoSingleInfoSuccessTest)
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
    EXPECT_EQ("*" , testArray[1].name());
    EXPECT_EQ("null" , testArray[1].description());
    EXPECT_EQ("group2" , testArray[2].name());
    EXPECT_EQ("group2new" , testArray[2].description());
}

TEST(GroupInfoServiceTest , DeleteInfoSuccessTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn( new TcpConnection(&g_Initializer.getEventLoop(),
                                "conn" , socketfd , localAddr , remoteAddr) );
    conn->setContext(mutex);
    STDSTR groupName("group2");
    STDSTR username("ddcnmb");
    STDSTR userBelong2Domain("domain1");
    STDSTR userBelong2Group("*");
    unsigned int identity = 0b00000010;
    Token token(username , identity , userBelong2Domain , userBelong2Group);
    GroupDestroyMsg* tmp =  new GroupDestroyMsg;
    tmp->set_token(token.toString());
    tmp->set_groupname(groupName);
    MessagePtr msg(tmp);
    Timestamp time;
    GroupInfoService waiter;
    waiter.onDeleteInfo(conn , msg , time);
    sleep(3);
    ConnectionPtr dbConn = Initializer::getDbPool().getConnection<MysqlConnection>();
    ResultSetPtr result = dbConn->executeQuery("select description\
                            from GROUP_INFO where name = 'group2'");
    STDSTR testDes("haha");
    if(result->next())
        testDes = result->getString(1);
    EXPECT_EQ("haha" , testDes);
}