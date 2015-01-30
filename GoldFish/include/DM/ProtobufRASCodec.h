#ifndef PROTOBUF_RAS_CODEC_H
#define PROTOBUF_RAS_CODEC_H

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <google/protobuf/message.h>

#include <muduo/net/Buffer.h>
#include <muduo/net/TcpConnection.h>

/*
struct ProtobufTransportFormat __attribute__ ((__packed__))
{
    uint32_t  cmd;
    uint32_t  length;
    uint32_t  error;
    uint32_t  para1;
    uint32_t  para2;
    char      protobufData[length];
}
*/

typedef boost::shared_ptr<google::protobuf::Message> MessagePtr;

class ProtobufRASCodec : boost::noncopyable
{
public:

    enum ErrorCode
    {
        kNoError = 0,
        kInvalidLength,
        kUnknownMessageType,
        kParseError,
    };

    typedef boost::function<void (muduo::net::TcpConnectionPtr const&,
                                  MessagePtr const&,
                                  muduo::Timestamp)> ProtobufMessageCallback;

    typedef boost::function<void (muduo::net::TcpConnectionPtr const&,
                                  muduo::net::Buffer*,
                                  muduo::Timestamp,
                                  ErrorCode)> ErrorCallback;

    explicit ProtobufRASCodec(ProtobufMessageCallback const& messageCb)
                                        : messageCallback_(messageCb),
                                          errorCallback_(defaultErrorCallback)
    {
    }

    ProtobufRASCodec(ProtobufMessageCallback const& messageCb , ErrorCallback const& errorCb)
                                        : messageCallback_(messageCb),
                                          errorCallback_(errorCb)
    {
    }

    void onMessage(muduo::net::TcpConnectionPtr const& conn,
                   muduo::net::Buffer* buf,
                   muduo::Timestamp receiveTime);

    void send(muduo::net::TcpConnectionPtr const& conn,
              google::protobuf::Message const& message,
              uint32_t error,
              uint32_t para1,
              uint32_t para2)
    {
        muduo::net::Buffer buf;
        fillEmptyBuffer(&buf, message , error , para1 , para2);
        conn->send(&buf);
    }

    static muduo::string const& errorCodeToString(ErrorCode errorCode);

    static void fillEmptyBuffer(muduo::net::Buffer* buf,
                                google::protobuf::Message const& message,
                                uint32_t error,
                                uint32_t para1,
                                uint32_t para2);

    static google::protobuf::Message* createMessage(std::string const& type_name);
    static MessagePtr parse(char const* buf, int len, uint32_t cmd , ErrorCode* errorCode);

private:

    static void defaultErrorCallback(muduo::net::TcpConnectionPtr const&,
                                     muduo::net::Buffer*,
                                     muduo::Timestamp,
                                     ErrorCode);

    ProtobufMessageCallback messageCallback_;
    ErrorCallback errorCallback_;

    static int const kHeaderLen = ( sizeof(uint32_t) )*5;
    static int const kMinMessageLen = 0;
    static int const kMaxMessageLen = 64*1024*1024;
};

#endif
