#include <string>
#include <sys/socket.h>

#include <DM/ProtobufRASCodec.h>
#include <DM/Initializer.h>
#include <DM/Config.h>
#include <DM/Config.h>

#include <muduo/net/TcpConnection.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Mutex.h>
#include <muduo/base/Types.h>

#include <boost/shared_ptr.hpp>

#include "gtest/gtest.h"

using namespace muduo;
using namespace muduo::net;

extern Initializer g_Initializer;

MessagePtr g_msg;

void testCallback(TcpConnectionPtr const& conn , MessagePtr msg , Timestamp time)
{
    g_msg = msg;
}

TEST(RASProtobufCodecTest , PraseTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn( new TcpConnection(&g_Initializer.getEventLoop(),
        "conn" , socketfd , localAddr , remoteAddr) );
    g_Initializer.registeRASMsg(5 , "MSG_CLIENT_DM_USER_CREATE");
    g_Initializer.registeRASMsg(6 , "MSG_DM_CLIENT_USER_CREATE_ACK");
    ProtobufRASCodec codec(&testCallback);
    Buffer buf;
    UserCreateMsg msg1;
    msg1.set_token("a");
    msg1.set_domainname("b");
    msg1.set_username("c");
    UserCreateACK msg2;
    msg2.set_statuscode(-5);
    ProtobufRASCodec::fillEmptyBuffer(&buf , msg1);
    Timestamp time;
    codec.onMessage(conn , &buf , time);
    UserCreateMsgPtr result = muduo::down_pointer_cast<UserCreateMsg>(g_msg);
    EXPECT_EQ("a" , result->token());
    EXPECT_EQ("b" , result->domainname());
    EXPECT_EQ("c" , result->username());
    Buffer buf1;
    ProtobufRASCodec::fillEmptyBuffer(&buf1 , msg2);
    codec.onMessage(conn , &buf1 , time);
    UserCreateACKPtr result1 = muduo::down_pointer_cast<UserCreateACK>(g_msg);
    EXPECT_EQ(-5 , result1->statuscode());
}