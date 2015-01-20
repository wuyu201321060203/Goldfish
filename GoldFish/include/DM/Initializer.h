#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <string>

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

private:

    ProtobufDispatcher _dispatcher;
    ProtobufCodec _codec;
    muduo::ThreadPool _pool;
    muduo::net::EventLoop _loop;
    ConfigLoader _loader;
    Options _options;
    std::string _path;

private:

    void onUnknownMessage(muduo::net::TcpConnectionPtr const& , MessagePtr const&,
                          muduo::Timestamp);
    inline bool parseCommandLine(int  , char**);

};

#endif