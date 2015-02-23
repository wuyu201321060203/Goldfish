#include "RASServer.h"

#include <muduo/net/EventLoop.h>
#include <DM/Initializer.h>

using namespace muduo;
using namespace muduo::net;

int main(void)
{
    InetAddress addr("127.0.0.1" , 9877);
    RASServer server(&Initializer::getEventLoop() , addr);
    server.start();
    ( Initializer::getEventLoop() ).loop();
    return 0;
}