#include <string>
#include <string.h>

#include <google/protobuf/descriptor.h>

#include <muduo/base/Logging.h>
#include <muduo/net/Endian.h>
#include <muduo/net/protorpc/google-inl.h>

#include <DM/ProtobufRASCodec.h>
#include <DM/Initializer.h>

using namespace muduo;
using namespace muduo::net;

Cmd2TypeNameMap ProtobufRASCodec::_cmd2TypeName;
TypeName2CmdMap ProtobufRASCodec::_typeName2Cmd;

void ProtobufRASCodec::fillEmptyBuffer(Buffer* buf,
                                       google::protobuf::Message const& message)
{
    assert(buf->readableBytes() == 0);
    std::string const& typeName = message.GetTypeName();
    uint32_t cmd = getCmdByTypename(typeName);
    buf->appendInt32(cmd);
    GOOGLE_DCHECK(message.IsInitialized()) <<
        InitializationErrorMessage("serialize", message);
    int byte_size = message.ByteSize();
    uint32_t len = byte_size;
    uint32_t error = -1;
    uint32_t para1 = -1;
    uint32_t para2 = -1;
    buf->appendInt32(len);
    buf->appendInt32(error);
    buf->appendInt32(para1);
    buf->appendInt32(para2);
    buf->ensureWritableBytes(byte_size);
    uint8_t* start = reinterpret_cast<uint8_t*>(buf->beginWrite());
    uint8_t* end = message.SerializeWithCachedSizesToArray(start);
    if (end - start != byte_size)
    {
        ByteSizeConsistencyError(byte_size, message.ByteSize(),
            static_cast<int>(end - start));
    }
    buf->hasWritten(byte_size);
    assert(buf->readableBytes() == kHeaderLen + byte_size);
}

namespace
{
    muduo::string const kNoErrorStr = "NoError";
    muduo::string const kInvalidLengthStr = "InvalidLength";
    muduo::string const kUnknownMessageTypeStr = "UnknownMessageType";
    muduo::string const kParseErrorStr = "ParseError";
    muduo::string const kUnknownErrorStr = "UnknownError";
}

muduo::string const& ProtobufRASCodec::errorCodeToString(ErrorCode errorCode)
{
    switch (errorCode)
    {
    case kNoError:
        return kNoErrorStr;
    case kInvalidLength:
        return kInvalidLengthStr;
    case kUnknownMessageType:
        return kUnknownMessageTypeStr;
    case kParseError:
        return kParseErrorStr;
    default:
        return kUnknownErrorStr;
    }
}

void ProtobufRASCodec::defaultErrorCallback(TcpConnectionPtr const& conn,
                                            Buffer* buf,
                                            Timestamp,
                                            ErrorCode errorCode)
{
    LOG_ERROR << "ProtobufRASCodec::defaultErrorCallback - " <<
                                                        errorCodeToString(errorCode);
    if(conn && conn->connected())
    {
        conn->shutdown();
    }
}

void ProtobufRASCodec::onMessage(TcpConnectionPtr const& conn,
                                 Buffer* buf,
                                 Timestamp receiveTime)
{
    while(buf->readableBytes() >= kMinMessageLen + kHeaderLen)
    {
        uint32_t cmd;
        uint32_t len;
        ::memcpy(&cmd , buf->peek() , sizeof(cmd) );
        cmd = sockets::hostToNetwork32(cmd);
        ::memcpy(&len , ( buf->peek() ) + sizeof(cmd) , sizeof(len) );
        len = sockets::hostToNetwork32(len);
        if(len > kMaxMessageLen)
        {
            _errorCallback(conn , buf , receiveTime , kInvalidLength);
            break;
        }
        else if(buf->readableBytes() >= implicit_cast<size_t>(len + kHeaderLen))
        {
            ErrorCode errorCode = kNoError;
            MessagePtr message = parse(buf->peek()+kHeaderLen , len , cmd , &errorCode);
            if(errorCode == kNoError && message)
            {
                _messageCallback(conn , message , receiveTime);
                buf->retrieve(kHeaderLen+len);
            }
            else
            {
                _errorCallback(conn , buf , receiveTime , errorCode);
                break;
            }
        }
        else
            break;
    }
}

google::protobuf::Message* ProtobufRASCodec::createMessage(std::string const& typeName)
{
    google::protobuf::Message* message = NULL;
    google::protobuf::Descriptor const* descriptor =
        google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(typeName);
    if(descriptor)
    {
        google::protobuf::Message const* prototype =
            google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
        if(prototype)
        {
            message = prototype->New();
        }
    }
    return message;
}

MessagePtr ProtobufRASCodec::parse(char const* buf , int len , uint32_t cmd,
                                   ErrorCode* error)
{
    MessagePtr message;
    std::string typeName = getTypenameByCmd(cmd);//TODO
    message.reset(createMessage(typeName));
    if(message)
    {
        if(message->ParseFromArray(buf, len))
            *error = kNoError;
        else
            *error = kParseError;
    }
    else
        *error = kUnknownMessageType;
    return message;
}

uint32_t ProtobufRASCodec::getCmdByTypename(STDSTR const& typeName)
{
    return _typeName2Cmd[typeName];
}

STDSTR ProtobufRASCodec::getTypenameByCmd(uint32_t cmd)
{
    return _cmd2TypeName[cmd];
}

void ProtobufRASCodec::registeRASMsg(uint32_t const& cmd , STDSTR const& typeName)
{
    _cmd2TypeName.insert(Cmd2TypeNameMap::value_type(cmd , typeName));
    _typeName2Cmd.insert(TypeName2CmdMap::value_type(typeName , cmd));
}
