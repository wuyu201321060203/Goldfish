#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <unistd.h>

#include <muduo/base/Types.h>

#include <DM/Config.h>
#include <DM/util.h>
#include <DM/UserManager.h>
#include <DM/Initializer.h>
#include <Db/ConnectionPool.h>
#include <Db/ResultSet.h>
#include <Db/Connection.h>
#include <DM/Token.h>
#include <mysql/MysqlConnection.h>

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;

UserLoginACK testLogin;
TokenIdentifyACK testVerifyToken;

TEST(UserManagerTest , LoginSuccessTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn( new TcpConnection(&Initializer::getEventLoop(),
                                "conn" , socketfd , localAddr , remoteAddr) );
    UserLoginMsg* tmp =  new UserLoginMsg;
    tmp->set_username("ddcnmb");
    tmp->set_password("ddsb");
    MessagePtr msg(tmp);
    Timestamp time;
    UserManager waiter;
    waiter.onUserLogin(conn , msg , time);
    sleep(3);
    EXPECT_EQ("helloworld" , testLogin.token());
    EXPECT_EQ("127.0.0.1" , testLogin.dcip());
    EXPECT_EQ(9877 , testLogin.dcport());
}

TEST(UserManagerTest , LoginFailTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn( new TcpConnection(&Initializer::getEventLoop(),
                                "conn" , socketfd , localAddr , remoteAddr) );
    UserLoginMsg* tmp =  new UserLoginMsg;
    tmp->set_username("ddcnmb");
    tmp->set_password("ddcnmb");
    MessagePtr msg(tmp);
    Timestamp time;
    UserManager waiter;
    waiter.onUserLogin(conn , msg , time);
    sleep(3);
    EXPECT_EQ(UNEXISTED_USER , testLogin.statuscode());
}

TEST(UserManagerTest , VerifyTokenTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn( new TcpConnection(&Initializer::getEventLoop(),
        "conn" , socketfd , localAddr , remoteAddr) );
    TokenIdentifyMsg* tmp =  new TokenIdentifyMsg;
    tmp->set_encryptedtoken("helloworld");
    MessagePtr msg(tmp);
    Timestamp time;
    UserManager waiter;
    (waiter.getTokenList()).push_back("helloworld");
    waiter.onVerifyEncryptedToken(conn , msg , time);
    sleep(3);
    EXPECT_EQ(SUCCESS , testVerifyToken.statuscode());
    EXPECT_EQ("helloworld" , testVerifyToken.rawtoken());
}

TEST(UserManagerTest , VerifyTokenSuccessTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn( new TcpConnection(&Initializer::getEventLoop(),
        "conn" , socketfd , localAddr , remoteAddr) );
    TokenIdentifyMsg* tmp =  new TokenIdentifyMsg;
    tmp->set_encryptedtoken("helloworld");
    MessagePtr msg(tmp);
    Timestamp time;
    UserManager waiter;
    (waiter.getTokenList()).push_back("helloworld");
    waiter.onVerifyEncryptedToken(conn , msg , time);
    sleep(3);
    EXPECT_EQ(SUCCESS , testVerifyToken.statuscode());
    EXPECT_EQ("helloworld" , testVerifyToken.rawtoken());
}

TEST(UserManagerTest , VerifyTokenFailTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn( new TcpConnection(&Initializer::getEventLoop(),
        "conn" , socketfd , localAddr , remoteAddr) );
    TokenIdentifyMsg* tmp =  new TokenIdentifyMsg;
    tmp->set_encryptedtoken("helloworld1");
    MessagePtr msg(tmp);
    Timestamp time;
    UserManager waiter;
    (waiter.getTokenList()).push_back("helloworld");
    waiter.onVerifyEncryptedToken(conn , msg , time);
    sleep(3);
    EXPECT_EQ(TOKEN_AUTH_FAIL , testVerifyToken.statuscode());
}