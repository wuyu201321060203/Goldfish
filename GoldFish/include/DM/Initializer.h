#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <string>
#include <map>

#include <muduo/net/EventLoop.h>
#include <muduo/base/ThreadPool.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>

#include "ProtobufCodec.h"
#include "ProtobufDispatcher.h"
#include "ConfigLoader.h"
#include "Options.h"
#include <Db/ConnectionPool.h>

class HeartBeatManager;

typedef std::map<uint32_t , std::string> Cmd2TypeNameMap;
typedef std::map<std::string , uint32_t> TypeName2CmdMap;

class Initializer
{
public:

    static int init(int , char**);
    static ProtobufCodec& getCodec();
    static ProtobufDispatcher& getDispatcher();
    static muduo::ThreadPool& getThreadPool();
    static muduo::net::EventLoop& getEventLoop();
    static Options& getOptions();
    static uint32_t getCmdByTypename(std::string const&);
    static std::string getTypenameByCmd(uint32_t);
    static void registeRASMsg(uint32_t const& , std::string const&);
    static OOzdb::ConnectionPool& getDbPool();
    static HeartBeatManager& getHeartBeatManager();

    static uint32_t getFrameworkID();

    static uint32_t getFrameworkInstanceID();

    static uint16_t getCliPort();

    static uint16_t getDCPort();

    static std::string getRCIP();

    static uint16_t getRCPort();

private:

    static ProtobufDispatcher _dispatcher;
    static ProtobufCodec _codec;
    static muduo::ThreadPool _threadPool;
    static muduo::net::EventLoop _loop;
    static ConfigLoader _loader;
    static Options _options;
    static std::string _path;
    static Cmd2TypeNameMap _cmd2TypeName;
    static TypeName2CmdMap _typeName2Cmd;
    static OOzdb::ConnectionPool _dbPool;
    static HeartBeatManager _heartbeatManager;
    static uint32_t _frameworkID;
    static uint32_t _frameworkInstanceID;
    static uint16_t _cliPort;
    static uint16_t _dcPort;
    static std::string _rcIP;
    static uint16_t _rcPort;

private:

    static void onUnknownMessage(muduo::net::TcpConnectionPtr const& , MessagePtr const&,
                          muduo::Timestamp);

    static bool parseCommandLine(int  , char**);
    static bool parseCommandLineDull(int  , char**);

};

#endif