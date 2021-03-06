#include <iostream>

#include <boost/bind.hpp>
#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>

#include <muduo/base/Logging.h>

#include <DM/Config.h>
#include <DM/Initializer.h>
#include <DM/HeartBeatManager.h>
#include <DM/DesEcbService.h>
#include <DM/DesEcbService.h>

namespace po = boost::program_options;

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;

ProtobufDispatcher Initializer::_dispatcher(
            boost::bind(&Initializer::onUnknownMessage , _1 , _2 , _3));

ProtobufCodec Initializer::_codec(
            boost::bind(&ProtobufDispatcher::onProtobufMessage , &_dispatcher , _1, _2 , _3));

muduo::ThreadPool Initializer::_threadPool;

muduo::net::EventLoop Initializer::_loop;

ConfigLoader Initializer::_loader;

Options Initializer::_options;

std::string Initializer::_path;

ConnectionPool Initializer::_dbPool(DB_URL);

CryptographicServicePtr Initializer::_desEcbAcceptor(new DesEcbService);

uint32_t Initializer::_frameworkID = 0;

uint32_t Initializer::_frameworkInstanceID = 0;

uint32_t Initializer::_selfModuleID = 0;

uint16_t Initializer::_cliPort = 0;

uint16_t Initializer::_dcPort = 0;

std::string Initializer::_rcIP;

uint16_t Initializer::_rcPort = 0;

std::string Initializer::_selfIP;

int Initializer::init(int argc , char** argv)
{
    if(parseCommandLineDull(argc , argv))
    {
        _threadPool.start(DEFAULT_THREADS);
        _loader.setConfigFilePath(_path);
        _loader.loadConfig(_options);
        return RET_SUCCESS;
    }
    else
    {
#ifdef DMDEBUG
        LOG_INFO << "fail to parse command line";
#endif
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

ConnectionPool& Initializer::getDbPool()
{
    return _dbPool;
}

CryptographicServicePtr const& Initializer::getDesEcbAcceptor()
{
    return _desEcbAcceptor;
}

uint32_t Initializer::getFrameworkID()
{
    return _frameworkID;
}

uint32_t Initializer::getFrameworkInstanceID()
{
    return _frameworkInstanceID;
}

uint32_t Initializer::getSelfModuleID()
{
    return _selfModuleID;
}

uint16_t Initializer::getCliPort()
{
    return _cliPort;
}

uint16_t Initializer::getDCPort()
{
    return _dcPort;
}

std::string Initializer::getRCIP()
{
    return _rcIP;
}

uint16_t Initializer::getRCPort()
{
    return _rcPort;
}

std::string Initializer::getSelfIP()
{
    return _selfIP;
}

void Initializer::onUnknownMessage(TcpConnectionPtr const& conn , MessagePtr const& msg,
                                   Timestamp receiveTime)
{
#ifdef DMDEBUG
    LOG_INFO << "onUnknownMessage:" << msg->GetTypeName();
#endif
}

/*the function is not used now but it is a good solution*/
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

bool Initializer::parseCommandLineDull(int argc , char* argv[])
{
    _path = CONFIG_FILE_PATH;
    STDSTR frameworkID(argv[1]);
    STDSTR frameworkInstanceID(argv[2]);
    STDSTR selfModuleID(argv[3]);
    STDSTR cliPort(argv[4]);
    STDSTR dcPort(argv[5]);
    STDSTR rcIP(argv[6]);
    STDSTR rcPort(argv[7]);
    STDSTR selfIP(argv[8]);
    _frameworkID = boost::lexical_cast<uint32_t>(frameworkID);
    _frameworkInstanceID = boost::lexical_cast<uint32_t>(frameworkInstanceID);
    _selfModuleID = boost::lexical_cast<uint32_t>(selfModuleID);
    _cliPort = boost::lexical_cast<uint16_t>(cliPort);
    _dcPort = boost::lexical_cast<uint16_t>(dcPort);
    _rcIP = rcIP;
    _rcPort = boost::lexical_cast<uint16_t>(rcPort);
    _selfIP = selfIP;
    return true;
}