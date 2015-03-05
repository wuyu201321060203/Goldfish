#include <utility>
#include <stdio.h>
#include <unistd.h>
#include <cassert>

#include <boost/bind.hpp>
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>

#include <muduo/net/TcpClient.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>

#include <DM/ProtobufCodec.h>
#include <DM/Config.h>
#include <DM/ProtobufDispatcher.h>
#include <DM/Token.h>
#include <DM/Initializer.h>

using namespace muduo;
using namespace muduo::net;

namespace po = boost::program_options;

class DMClient : boost::noncopyable
{
public:

    DMClient(EventLoop* loop, InetAddress const& listenAddr)
        : loop_(loop),
        client_(loop, listenAddr, "DMClient"),
        dispatcher_(boost::bind(&DMClient::onUnknownMessage,
            this , _1 , _2 , _3)),
        codec_(boost::bind(&ProtobufDispatcher::onProtobufMessage,
            &dispatcher_, _1 , _2 , _3))
    {
        dispatcher_.registerMessageCallback(
            DomainCreateACK::descriptor(),
            boost::bind(&DMClient::onMessage , this , _1 , _2 , _3));

        client_.setConnectionCallback(
            boost::bind(&DMClient::onConnection, this, _1));

        client_.setMessageCallback(
            boost::bind(&ProtobufCodec::onMessage, &codec_, _1, _2, _3));
    }

    void connect()
    {
        client_.connect();
    }

private:

    void onConnection(TcpConnectionPtr const& conn)
    {
        LOG_TRACE << conn->localAddress().toIpPort() << " -> "
            << conn->peerAddress().toIpPort() << " is "
            << (conn->connected() ? "UP" : "DOWN");

        if (conn->connected())
        {
            GroupCreateMsg apply;
            STDSTR username("ddcnmb");
            STDSTR userBelong2Domain("*");
            STDSTR userBelong2Group("*");
            unsigned int identity = 0b00000000;
            Token token(username , identity , userBelong2Domain , userBelong2Group);
            apply.set_token(token.toString());
            apply.set_groupname("net");
            apply.set_groupdescription("net");
            apply.set_belong2domain("domain1");
            codec_.send(conn , apply);
        }
    }

    void onMessage(TcpConnectionPtr const& conn, MessagePtr const& msg, Timestamp time)
    {
        LOG_TRACE << conn->name() << " recv " << msg->ByteSize() << " bytes at " << time.toString();
        GroupCreateACKPtr respond = muduo::down_pointer_cast<GroupCreateACK>(msg);
        assert(respond->statuscode() == 0);
    }

    void onUnknownMessage(TcpConnectionPtr const& conn,
        MessagePtr const& msg,
        Timestamp receiveTime)
    {
        LOG_INFO << "onUnknownMessage:" << msg->GetTypeName();
    }

    EventLoop* loop_;
    TcpClient client_;
    ProtobufDispatcher dispatcher_;
    ProtobufCodec codec_;
};


bool parseCommandLine(int argc , char* argv[] , std::string* ip,
                      uint16_t* port)
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Help")
        ("port,p", po::value<uint16_t>(port), "TCP port")
        ("ip,i" , po::value<std::string>(ip), "ip of server");
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

int main(int argc, char* argv[])
{
    std::string ip = "127.0.0.1";
    uint16_t port = 9877;
    if(parseCommandLine(argc , argv , &ip , &port))
    {
        InetAddress serverAddr(ip , port);
        boost::shared_ptr<DMClient> client( new DMClient(&Initializer::getEventLoop(), serverAddr) );
        client->connect();
        Initializer::getEventLoop().loop();
    }
    return 0;
}
