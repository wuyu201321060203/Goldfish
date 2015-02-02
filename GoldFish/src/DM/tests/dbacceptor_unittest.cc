#include <string>
#include <sys/socket.h>
#include <unistd.h>

#include <DM/DbAcceptor.h>
#include <DM/Initializer.h>
#include <DM/Config.h>
#include <Db/ConnectionPool.h>
#include <Db/ResultSet.h>
#include <Db/Connection.h>
#include <mysql/MysqlConnection.h>
#include <DM/Config.h>

#include <muduo/net/TcpConnection.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Mutex.h>

#include <boost/shared_ptr.hpp>

#include "gtest/gtest.h"

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;

//extern Initializer g_Initializer;
//extern OOzdb::ConnectionPool Initializer::getDbPool();

ConfigPersistenceACK tPreserveACK;
ConfigLookupACK tLookUpACK;
ConfigDeleteACK tDeleteACK;

typedef boost::shared_ptr<MutexLock> MutexLockPtr;
MutexLockPtr mutex(new MutexLock);

TEST(DbAcceptorTest , PreserveSuccessTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn(new TcpConnection(&Initializer::getEventLoop(),
                            "test" , socketfd , localAddr , remoteAddr));
    conn->setContext(mutex);
    ConfigPersistenceMsg* msg = new ConfigPersistenceMsg;
    msg->set_domainname("domain1");
    msg->add_raip("192.168.1.0");
    msg->add_raip("192.168.1.1");
    MessagePtr message(msg);
    Timestamp time;
    DbAcceptor acceptor;
    acceptor.onPreserve(conn , message , time);
    sleep(3);
    ConnectionPtr dbConn = Initializer::getDbPool().getConnection<MysqlConnection>();
    ResultSetPtr result = dbConn->executeQuery(
                "select raIP from IMCONFIG_INFO where domainName = 'domain1'");
    std::string ip1("192.168.1.0");
    std::string ip2("192.168.1.1");
    std::string testIP;
    int flag = 0;
    while(result->next())
    {
        testIP = result->getString(1);
        if(0 == flag)
        {
            EXPECT_EQ(ip1 , testIP);
            ++flag;
        }
        else
            EXPECT_EQ(ip2 , testIP);
    }
    EXPECT_EQ(SUCCESS , tPreserveACK.statuscode());
}

TEST(DbAcceptorTest , PreserveFailTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn(new TcpConnection(&Initializer::getEventLoop(),
                            "test" , socketfd , localAddr , remoteAddr));
    conn->setContext(mutex);
    ConfigPersistenceMsg* msg = new ConfigPersistenceMsg;
    msg->set_domainname("domain2");
    msg->add_raip("192.168.1.0");
    msg->add_raip("192.168.1.1");
    MessagePtr message(msg);
    Timestamp time;
    DbAcceptor acceptor;
    acceptor.onPreserve(conn , message , time);
    sleep(3);
    EXPECT_EQ(CONFIG_PRESERVE_FAIL , tPreserveACK.statuscode());
}

TEST(DbAcceptorTest , LoadSuccessTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn(new TcpConnection(&Initializer::getEventLoop(),
        "test" , socketfd , localAddr , remoteAddr));
    conn->setContext(mutex);
    ConfigLookupMsg* msg = new ConfigLookupMsg;
    msg->set_domainname("domain1");
    MessagePtr message(msg);
    Timestamp time;
    DbAcceptor acceptor;
    acceptor.onLoad(conn , message , time);
    sleep(3);
    int size = tLookUpACK.raip_size();
    std::string ip1 = tLookUpACK.raip(0);
    std::string ip2 = tLookUpACK.raip(1);
    EXPECT_EQ("192.168.1.0" , ip1);
    EXPECT_EQ("192.168.1.1" , ip2);
    EXPECT_EQ(SUCCESS , tLookUpACK.statuscode());
}

TEST(DbAcceptorTest , LoadFailTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn(new TcpConnection(&Initializer::getEventLoop(),
        "test" , socketfd , localAddr , remoteAddr));
    conn->setContext(mutex);
    ConfigLookupMsg* msg = new ConfigLookupMsg;
    msg->set_domainname("domain2");
    MessagePtr message(msg);
    Timestamp time;
    DbAcceptor acceptor;
    acceptor.onLoad(conn , message , time);
    sleep(3);
    EXPECT_EQ(DOMAIN_NO_CONFIG , tLookUpACK.statuscode());
}

TEST(DbAcceptorTest , DeleteSuccessTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn(new TcpConnection(&Initializer::getEventLoop(),
                            "test" , socketfd , localAddr , remoteAddr));
    conn->setContext(mutex);
    ConfigDeleteMsg* msg = new ConfigDeleteMsg;
    msg->set_domainname("domain1");
    MessagePtr message(msg);
    Timestamp time;
    DbAcceptor acceptor;
    acceptor.onDelete(conn , message , time);
    sleep(3);
    EXPECT_EQ(SUCCESS , tDeleteACK.statuscode());
}

TEST(DbAcceptorTest , DeleteFailTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn(new TcpConnection(&Initializer::getEventLoop(),
                            "test" , socketfd , localAddr , remoteAddr));
    conn->setContext(mutex);
    ConfigDeleteMsg* msg = new ConfigDeleteMsg;
    msg->set_domainname("domain2");
    MessagePtr message(msg);
    Timestamp time;
    DbAcceptor acceptor;
    acceptor.onDelete(conn , message , time);
    sleep(3);
    EXPECT_EQ(DOMAIN_NO_CONFIG , tDeleteACK.statuscode());
}