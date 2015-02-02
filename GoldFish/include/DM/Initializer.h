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

private:

    static void onUnknownMessage(muduo::net::TcpConnectionPtr const& , MessagePtr const&,
                          muduo::Timestamp);

    static bool parseCommandLine(int  , char**);

};

#endif