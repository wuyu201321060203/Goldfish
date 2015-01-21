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

#include <muduo/net/TcpConnection.h>
#include <muduo/net/EventLoop.h>

#include "gtest/gtest.h"

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;

extern Initializer g_Initializer;
OOzdb::ConnectionPool g_DbPool("mysql://root:123@localhost:3306/DM");

TEST(DbAcceptorTest , PreserveTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn(new TcpConnection(&g_Initializer.getEventLoop() , "test" , socketfd , localAddr , remoteAddr));
    ConfigPersistenceMsg* msg = new ConfigPersistenceMsg;
    msg->set_domainname("domain1");
    msg->add_raip("192.168.1.0");
    msg->add_raip("192.168.1.1");
    MessagePtr message(msg);
    Timestamp time;
    DbAcceptor acceptor;
    acceptor.onPreserve(conn , message , time);
    ConnectionPtr dbConn = g_DbPool.getConnection<MysqlConnection>();
    ResultSetPtr result = dbConn->executeQuery("select raIP from IMCONFIG_INFO where domainName = 'domain1'");
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
}