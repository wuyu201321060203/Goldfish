#include <DM/Initializer.h>
#include <DM/DMServer.h>

int main(int argc , char** argv)
{
    Initializer::init(argc , argv);
    DMServer dmServer( &Initializer::getEventLoop() , Initializer::getOptions() );
    dmServer.start();
    ( Initializer::getEventLoop() ).loop();
    //never get here
    return 0;
}