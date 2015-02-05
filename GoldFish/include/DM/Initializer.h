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

    static void setFrameworkID(uint32_t);
    static uint32_t getFrameworkID();

    static void setFrameworkInstanceID(uint32_t);
    static uint32_t getFrameworkInstanceID();

    static void setDockerTag(std::string);
    static std::string getDockerTag();

    static void setExecFilePathList(std::string);
    static std::string getExecFilePathList();

    static void setCliPort(uint16_t);
    static uint16_t getCliPort();

    static void setDCPort(uint16_t);
    static uint16_t getDCPort();

    static void setRCIP(std::string);
    static std::string getRCIP();

    static void setRCPort(uint16_t);
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
    static uint32_t _frameworkID;
    static uint32_t _frameworkInstanceID;
    static std::string _dockerTag;
    static std::string _execFilePathList;
    static uint16_t _cliPort;
    static uint16_t _dcPort;
    static std::string _rcIP;
    static uint16_t _rcPort;

private:

    static void onUnknownMessage(muduo::net::TcpConnectionPtr const& , MessagePtr const&,
                          muduo::Timestamp);

    static bool parseCommandLine(int  , char**);

};

#endif