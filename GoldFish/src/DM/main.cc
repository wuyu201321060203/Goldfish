#include <DM/Initializer.h>
#include <DM/DMServer.h>
#include <DM/AsyncLogging.h>

#include <muduo/base/Logging.h>

AsyncLogging* g_asyncLog = NULL;

void asyncOutput(char const* msg, int len)
{
    g_asyncLog->append(msg, len);
}

int main(int argc , char** argv)
{
    Initializer::init(argc , argv);
    char name[256];
    strncpy(name, argv[0], 256);
    AsyncLogging log(::basename(name), ROLL_SIZE);
    log.start();
    g_asyncLog = &log;
    muduo::Logger::setOutput(asyncOutput);
    DMServer dmServer( &Initializer::getEventLoop() , Initializer::getOptions() );
    dmServer.start();
    LOG_INFO << "test success";
    ( Initializer::getEventLoop() ).loop();
    //never get here
    return 0;
}