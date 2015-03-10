#include "RASServer.h"

#include <muduo/net/EventLoop.h>
#include <DM/Initializer.h>

using namespace muduo;
using namespace muduo::net;

int main(void)
{
    InetAddress addr("192.168.1.126" , 9877);
    RASServer server(&Initializer::getEventLoop() , addr);
    server.start();
    ( Initializer::getEventLoop() ).loop();
    return 0;
}