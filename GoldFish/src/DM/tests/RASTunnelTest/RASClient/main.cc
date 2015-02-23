#include <DM/RASTunnel.h>
#include <DM/Initializer.h>
#include <DM/RemoteDomainInfoService.h>
#include <DM/ResourceManager.h>

#include <boost/shared_ptr.hpp>

using namespace muduo;
using namespace muduo::net;

int main(void)
{
    char* config[9] = {"test" , "1" , "2" , "3" ,  "4" , "5" , "0.0" , "5" , "0.1"};
    Initializer::init(9 , config);
    InetAddress serverAddr("127.0.0.1" , 9877);
    boost::shared_ptr<RASTunnel> client(
        new RASTunnel(&Initializer::getEventLoop() , serverAddr) );

    client->init();
    ( Initializer::getEventLoop() ).loop();
    return 0;
}