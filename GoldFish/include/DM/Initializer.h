#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <string>

#include <muduo/net/EventLoop.h>
#include <muduo/base/ThreadPool.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>

#include "ProtobufCodec.h"
#include "ProtobufRASCodec.h"
#include "ProtobufDispatcher.h"
#include "ConfigLoader.h"
#include "Options.h"
#include "CryptographicService.h"
#include <Db/ConnectionPool.h>

class HeartBeatManager;

class Initializer
{
public:

    static int init(int , char**);
    static ProtobufCodec& getCodec();
    static ProtobufDispatcher& getDispatcher();
    static muduo::ThreadPool& getThreadPool();
    static muduo::net::EventLoop& getEventLoop();
    static Options& getOptions();
    static OOzdb::ConnectionPool& getDbPool();
    static CryptographicServicePtr const& getDesEcbAcceptor();

    static uint32_t getFrameworkID();

    static uint32_t getFrameworkInstanceID();

    static uint32_t getSelfModuleID();

    static uint16_t getCliPort();

    static uint16_t getDCPort();

    static std::string getRCIP();

    static uint16_t getRCPort();

    static std::string getSelfIP();

private:

    static ProtobufDispatcher _dispatcher;
    static ProtobufCodec _codec;
    static muduo::ThreadPool _threadPool;
    static muduo::net::EventLoop _loop;
    static ConfigLoader _loader;
    static Options _options;
    static std::string _path;
    static OOzdb::ConnectionPool _dbPool;
    static CryptographicServicePtr _desEcbAcceptor;
    static uint32_t _frameworkID;
    static uint32_t _frameworkInstanceID;
    static uint32_t _selfModuleID;
    static uint16_t _cliPort;
    static uint16_t _dcPort;
    static std::string _rcIP;
    static uint16_t _rcPort;
    static std::string _selfIP;

private:

    static void onUnknownMessage(muduo::net::TcpConnectionPtr const& , MessagePtr const&,
                          muduo::Timestamp);

    static bool parseCommandLine(int  , char**);
    static bool parseCommandLineDull(int  , char**);

};

#endif