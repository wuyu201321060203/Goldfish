#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

#include <DM/Initializer.h>
#include <DM/Config.h>
#include <DM/HeartBeatManager.h>

#include <muduo/net/TcpConnection.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Mutex.h>

#include "gtest/gtest.h"

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;

void test()
{
}

TEST(HeartBeatManagerTest , getDCListTest)
{
    InetAddress localAddr(10);
    InetAddress remoteAddr(100);
    int socketfd = ::socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    TcpConnectionPtr conn1(new TcpConnection(&Initializer::getEventLoop(),
                            "conn1" , socketfd , localAddr , remoteAddr));
    TcpConnectionPtr conn2(new TcpConnection(&Initializer::getEventLoop(),
                            "conn2" , socketfd , localAddr , remoteAddr));

    HeartBeatManager manager;
    manager.setEventLoop(&Initializer::getEventLoop());
    manager.delegateTimerTask(0 , 0 , 0 , &test , conn1);
    manager.delegateTimerTask(0 , 0 , 0 , &test , conn2);
    std::vector<TcpConnectionWeakPtr> testArray;
    manager.getDCList(testArray);
    EXPECT_EQ("conn1" , (testArray[0].lock())->name() );
    EXPECT_EQ("conn2" , (testArray[1].lock())->name() );
}