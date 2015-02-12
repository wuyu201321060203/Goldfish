#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <unistd.h>

#include <muduo/base/Types.h>

#include <DM/Config.h>
#include <DM/util.h>
#include <DM/UserInfoService.h>
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

typedef MSG_DM_CLIENT_USER_INFO_GET_ACK_USER_INFO UserInfo;
std::vector<UserInfo> testArray1;

TEST(UserInfoServiceTest , CreateInfoSuccessTest)
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
    UserCreateMsg* tmp =  new UserCreateMsg;
    tmp->set_token(token.toString());
    tmp->set_domainname("domain1");
    tmp->set_groupname("group1");
    tmp->set_username("ddsb");
    tmp->set_password("ddsb");
    unsigned int identity1 = 0b00001000;
    tmp->set_authority(identity1);
    MessagePtr msg(tmp);
    Timestamp time;
    UserInfoService waiter;
    waiter.onCreateInfo(conn , msg , time);
    sleep(3);
    ConnectionPtr dbConn = Initializer::getDbPool().getConnection<MysqlConnection>();
    ResultSetPtr result = dbConn->executeQuery("select identity , passwd\
                            from USER_INFO where name = 'ddsb'");
    sleep(3);
    STDSTR testPasswd("haha");
    int testIdentity = -1;
    if(result->next())
    {
        testPasswd = result->getString(2);
        testIdentity = result->getInt(1);
    }
    EXPECT_EQ("ddsb" , testPasswd);
    EXPECT_EQ(8 , testIdentity);
//test create root
    tmp =  new UserCreateMsg;
    tmp->set_token(token.toString());
    tmp->set_domainname("*");
    tmp->set_groupname("*");
    tmp->set_username("ddrootsb");
    tmp->set_password("ddrootsb");
    unsigned int identity2 = 0b00000000;
    tmp->set_authority(identity2);
    MessagePtr msg1(tmp);
    Timestamp time1;
    waiter.onCreateInfo(conn , msg1 , time1);
    sleep(3);
    result = dbConn->executeQuery("select identity , passwd , belong2Domain\
                            , belong2Group from USER_INFO where name = 'ddrootsb'");
    sleep(3);
    STDSTR testPasswd1("haha");
    int testIdentity1 = -1;
    int testDomain = -1;
    int testGroup = -1;
    if(result->next())
    {
        testPasswd1 = result->getString(2);
        testIdentity1 = result->getInt(1);
        testDomain = result->getInt(3);
        testGroup = result->getInt(4);
    }
    EXPECT_EQ("ddrootsb" , testPasswd1);
    EXPECT_EQ(0 , testIdentity1);
    EXPECT_EQ(ROOT_DOMAIN , testDomain);
    EXPECT_EQ(ROOT_DOMAINADMIN_GROUP , testGroup);
//test create domainadmin
    tmp =  new UserCreateMsg;
    tmp->set_token(token.toString());
    tmp->set_domainname("domain1");
    tmp->set_groupname("*");
    tmp->set_username("ddsb1");
    tmp->set_password("ddsb1");
    unsigned int identity3 = 0b00000010;
    tmp->set_authority(identity3);
    MessagePtr msg2(tmp);
    Timestamp time2;
    waiter.onCreateInfo(conn , msg2 , time2);
    sleep(3);
    dbConn = Initializer::getDbPool().getConnection<MysqlConnection>();
    result = dbConn->executeQuery("select identity , passwd , belong2Domain ,\
                            belong2Group from USER_INFO where name = 'ddsb1'");
    sleep(3);
    STDSTR testPasswd2("haha");
    int testIdentity2 = -1;
    int testDomain1 = -1;
    int testGroup1 = -1;
    if(result->next())
    {
        testPasswd2 = result->getString(2);
        testIdentity2 = result->getInt(1);
        testDomain1 = result->getInt(3);
        testGroup1 = result->getInt(4);
    }
    EXPECT_EQ("ddsb1" , testPasswd2);
    EXPECT_EQ(2 , testIdentity2);
    EXPECT_EQ(1 , testDomain1);
    EXPECT_EQ(88 , testGroup1);
}

TEST(UserInfoServiceTest , GetSingleInfoSuccessTest)
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
    UserInfoGetMsg* tmp =  new UserInfoGetMsg;
    tmp->set_token(token.toString());
    MessagePtr msg(tmp);
    Timestamp time;
    UserInfoService waiter;
    waiter.onGetInfo(conn , msg , time);
    sleep(3);
    EXPECT_EQ("domain1" , testArray1[0].domainname());
    EXPECT_EQ("group1" , testArray1[0].groupname());
    EXPECT_EQ("ddcnmb" , testArray1[0].username());
    EXPECT_EQ("ddcnmb" , testArray1[0].password());
    EXPECT_EQ(2 , testArray1[0].authority());
}

TEST(UserInfoServiceTest , GetNoSingleInfoSuccessTest)
{
    testArray1.clear();
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn( new TcpConnection(&g_Initializer.getEventLoop(),
                                "conn" , socketfd , localAddr , remoteAddr) );
    conn->setContext(mutex);
    STDSTR username("ddcnmb");
    STDSTR userBelong2Domain("domain1");
    STDSTR userBelong2Group("*");
    unsigned int identity = 0b00000010;
    Token token(username , identity , userBelong2Domain , userBelong2Group);
    UserInfoGetMsg* tmp =  new UserInfoGetMsg;
    tmp->set_token(token.toString());
    MessagePtr msg(tmp);
    Timestamp time;
    UserInfoService waiter;
    waiter.onGetInfo(conn , msg , time);
    sleep(3);
    EXPECT_EQ("domain1" , testArray1[0].domainname());
    EXPECT_EQ("group1" , testArray1[0].groupname());
    EXPECT_EQ("ddcnmb" , testArray1[0].username());
    EXPECT_EQ("ddcnmb" , testArray1[0].password());
    EXPECT_EQ(2 , testArray1[0].authority());
    EXPECT_EQ("domain1" , testArray1[1].domainname());
    EXPECT_EQ("group1" , testArray1[1].groupname());
    EXPECT_EQ("ddsb" , testArray1[1].username());
    EXPECT_EQ("ddsb" , testArray1[1].password());
    EXPECT_EQ(8 , testArray1[1].authority());
}

TEST(UserInfoServiceTest , UpdateInfoSuccessTest)
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
    unsigned int identity = 0b00001001;
    Token token(username , identity , userBelong2Domain , userBelong2Group);
    UserInfoUpdateMsg* tmp =  new UserInfoUpdateMsg;
    tmp->set_token(token.toString());
    tmp->set_password("ddsb");
    MessagePtr msg(tmp);
    Timestamp time;
    UserInfoService waiter;
    waiter.onUpdateInfo(conn , msg , time);
    sleep(3);
    ConnectionPtr dbConn = Initializer::getDbPool().getConnection<MysqlConnection>();
    ResultSetPtr result = dbConn->executeQuery("select passwd from USER_INFO\
         where name = 'ddcnmb'");
    STDSTR testPasswd("xx");
    if(result->next())
        testPasswd = result->getString(1);
    EXPECT_EQ("ddsb" , testPasswd);
}

/*
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
*/

TEST(UserInfoServiceTest , DeleteInfoSuccessTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn( new TcpConnection(&g_Initializer.getEventLoop(),
                                "conn" , socketfd , localAddr , remoteAddr) );
    conn->setContext(mutex);
    STDSTR username("ddcnmb");
    STDSTR userBelong2Domain("domain1");
    STDSTR userBelong2Group("*");
    unsigned int identity = 0b00000010;
    Token token(username , identity , userBelong2Domain , userBelong2Group);
    UserDestroyMsg* tmp =  new UserDestroyMsg;
    tmp->set_token(token.toString());
    tmp->set_username("ddsb");
    MessagePtr msg(tmp);
    Timestamp time;
    UserInfoService waiter;
    waiter.onDeleteInfo(conn , msg , time);
    sleep(3);
    ConnectionPtr dbConn = Initializer::getDbPool().getConnection<MysqlConnection>();
    ResultSetPtr result = dbConn->executeQuery("select passwd , identity \
                            from USER_INFO where name = 'ddsb'");
    STDSTR testPasswd("haha");
    int testIdentity = -1;
    if(result->next())
    {
        testPasswd = result->getString(1);
        identity = result->getInt(2);
    }
    EXPECT_EQ("haha" , testPasswd);
    EXPECT_EQ(-1 , testIdentity);
}