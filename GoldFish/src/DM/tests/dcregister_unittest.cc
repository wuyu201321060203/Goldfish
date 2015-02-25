#include "gtest/gtest.h"

#include <muduo/base/Types.h>
#include <muduo/net/TcpConnection.h>

#include <DM/Config.h>
#include <DM/util.h>
#include <DM/DCRegister.h>
#include <Db/ConnectionPool.h>
#include <Db/ResultSet.h>
#include <Db/Connection.h>
#include <DM/Initializer.h>
#include <mysql/MysqlConnection.h>

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;

extern Initializer g_Initializer;

TEST(DCRegisterTest , RegisterTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn( new TcpConnection(&g_Initializer.getEventLoop(),
                                "conn" , socketfd , localAddr , remoteAddr) );

    RegisterMsg* tmp =  new RegisterMsg;
    tmp->set_moduleid(88);
    tmp->set_ip("192.168.1.126");
    tmp->set_port(12345);
    MessagePtr msg(tmp);
    Timestamp time;
    DCRegister waiter;
    waiter.onMessage(conn , msg , time);
    sleep(3);
    ConnectionPtr dbConn = Initializer::getDbPool().getConnection<MysqlConnection>();
    ResultSetPtr result = dbConn->executeQuery("select IP , Port \
                            from DOMAIN_INFO where id = 88");
    STDSTR testIP;
    int testPort;
    if(result->next())
    {
        testIP = result->getString(1);
        testPort = result->getInt(2);
    }
    EXPECT_EQ("192.168.1.126" , testIP);
    EXPECT_EQ(12345 , testPort);
}