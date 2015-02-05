#include <iostream>

#include <boost/bind.hpp>
#include <boost/program_options.hpp>

#include <muduo/base/Logging.h>

#include <DM/Config.h>
#include <DM/Initializer.h>

namespace po = boost::program_options;

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;

ProtobufDispatcher Initializer::_dispatcher(
            boost::bind(&Initializer::onUnknownMessage , _1 , _2 , _3));

ProtobufCodec Initializer::_codec(
            boost::bind(&ProtobufDispatcher::onProtobufMessage , _dispatcher , _1, _2 , _3));

muduo::ThreadPool Initializer::_threadPool;

muduo::net::EventLoop Initializer::_loop;

ConfigLoader Initializer::_loader;

Options Initializer::_options;

std::string Initializer::_path;

Cmd2TypeNameMap Initializer::_cmd2TypeName;

TypeName2CmdMap Initializer::_typeName2Cmd;

ConnectionPool Initializer::_dbPool("mysql://root:123@localhost:3306/DM");

uint32_t Initializer::_frameworkID = 0;

uint32_t Initializer::_frameworkInstanceID = 0;

std::string Initializer::_dockerTag;

std::string Initializer::_execFilePathList;

uint16_t Initializer::_cliPort = 0;

uint16_t Initializer::_dcPort = 0;

std::string Initializer::_rcIP;

uint16_t Initializer::_rcPort = 0;

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

uint32_t Initializer::getCmdByTypename(STDSTR const& typeName)
{
    return _typeName2Cmd[typeName];
}

STDSTR Initializer::getTypenameByCmd(uint32_t cmd)
{
    return _cmd2TypeName[cmd];
}

void Initializer::registeRASMsg(uint32_t const& cmd , STDSTR const& typeName)
{
    _cmd2TypeName.insert(Cmd2TypeNameMap::value_type(cmd , typeName));
    _typeName2Cmd.insert(TypeName2CmdMap::value_type(typeName , cmd));
}

ConnectionPool& Initializer::getDbPool()
{
    return _dbPool;
}

void Initializer::setFrameworkID(uint32_t id)
{
    _frameworkID = id;
}

uint32_t Initializer::getFrameworkID()
{
    return _frameworkID;
}

void Initializer::setFrameworkInstanceID(uint32_t id)
{
    _frameworkInstanceID = id;
}

uint32_t Initializer::getFrameworkInstanceID()
{
    return _frameworkInstanceID;
}

void Initializer::setDockerTag(std::string tag)
{
    _dockerTag = tag;
}

std::string Initializer::getDockerTag()
{
    return _dockerTag;
}

void Initializer::setExecFilePathList(std::string path)
{
    _execFilePathList = path;
}

std::string Initializer::getExecFilePathList()
{
    return _execFilePathList;
}

void Initializer::setCliPort(uint16_t port)
{
    _cliPort = port;
}

uint16_t Initializer::getCliPort()
{
    return _cliPort;
}

void Initializer::setDCPort(uint16_t port)
{
    _dcPort = port;
}

uint16_t Initializer::getDCPort()
{
    return _dcPort;
}

void Initializer::setRCIP(std::string ip)
{
    _rcIP = ip;
}

std::string Initializer::getRCIP()
{
    return _rcIP;
}

void Initializer::setRCPort(uint16_t port)
{
    _rcPort = port;
}

uint16_t Initializer::getRCPort()
{
    return _rcPort;
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