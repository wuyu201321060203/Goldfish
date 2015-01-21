#include <iostream>

#include <boost/bind.hpp>
#include <boost/program_options.hpp>

#include <muduo/base/Logging.h>

#include <DM/Config.h>
#include <DM/Initializer.h>

namespace po = boost::program_options;
using namespace muduo;
using namespace muduo::net;

Initializer::Initializer()
    : _dispatcher(
            boost::bind(&Initializer::onUnknownMessage , this , _1 , _2 , _3)
       ),
      _codec(
            boost::bind(&ProtobufDispatcher::onProtobufMessage , _dispatcher , _1, _2 , _3)
       )
{
}

int Initializer::init(int argc , char** argv)
{
    if(parseCommandLine(argc , argv))
    {
        _threadPool.start(DEFAULT_THREADS);
        _loader.setConfigFilePath(_path);
        _loader.loadConfig(_options);
        return RET_SUCCESS;
    }
    else
    {
        LOG_INFO << "fail to parse command line";
        return RET_FAIL;
    }
}

ProtobufCodec& Initializer::getCodec()
{
    return _codec;
}

ProtobufDispatcher& Initializer::getDispatcher()
{
    return _dispatcher;
}

ThreadPool& Initializer::getThreadPool()
{
    return _threadPool;
}

EventLoop& Initializer::getEventLoop()
{
    return _loop;
}

Options& Initializer::getOptions()
{
    return _options;
}

void Initializer::onUnknownMessage(TcpConnectionPtr const& conn , MessagePtr const& msg,
                                   Timestamp receiveTime)
{
    LOG_INFO << "onUnknownMessage:" << msg->GetTypeName();
}

bool Initializer::parseCommandLine(int argc , char* argv[])
{
    _path = "./DMConfig.lua";
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Help")
        ("configfilePath,c" , po::value<std::string>(&_path),
            "Configure File Path");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    if(vm.count("help"))
    {
        std::cout << "\n";
        std::cout << desc << "\n";
        return false;
    }
    return true;
}