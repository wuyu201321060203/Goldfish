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

class Initializer
{
public:

    Initializer();
    int init(int , char**);
    ProtobufCodec& getCodec();
    ProtobufDispatcher& getDispatcher();
    muduo::ThreadPool& getThreadPool();
    muduo::net::EventLoop& getEventLoop();
    Options& getOptions();
    uint32_t getCmdByTypename(std::string const&);
    std::string getTypenameByCmd(uint32_t);
    void registeRASMsg(uint32_t const& , std::string const&);

private:

    ProtobufDispatcher _dispatcher;
    ProtobufCodec _codec;
    muduo::ThreadPool _threadPool;
    muduo::net::EventLoop _loop;
    ConfigLoader _loader;
    Options _options;
    std::string _path;
    typedef std::map<uint32_t , std::string> Cmd2TypeNameMap;
    Cmd2TypeNameMap _cmd2TypeName;
    typedef std::map<std::string , uint32_t> TypeName2CmdMap;
    TypeName2CmdMap _typeName2Cmd;

private:

    void onUnknownMessage(muduo::net::TcpConnectionPtr const& , MessagePtr const&,
                          muduo::Timestamp);

    inline bool parseCommandLine(int  , char**);

};

#endif