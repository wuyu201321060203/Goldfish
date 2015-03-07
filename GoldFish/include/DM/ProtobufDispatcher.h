#ifndef DISPATCHER_LITE_H
#define DISPATCHER_LITE_H

#include <muduo/net/Callbacks.h>
#include <muduo/base/Logging.h>

#include <google/protobuf/message.h>

#include <map>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<google::protobuf::Message> MessagePtr;

class ProtobufDispatcher
{
public:

    typedef boost::function<void (muduo::net::TcpConnectionPtr const&,
                                  MessagePtr const&,
                                  muduo::Timestamp)> ProtobufMessageCallback;

    explicit ProtobufDispatcher(ProtobufMessageCallback const& defaultCb)
        : _defaultCallback(defaultCb)
    {
    }

    void onProtobufMessage(muduo::net::TcpConnectionPtr const& conn,
                           MessagePtr const& message,
                           muduo::Timestamp receiveTime) const
    {
        CallbackMap::const_iterator it = _callbacks.find(message->GetDescriptor());
        if (it != _callbacks.end())
        {
            it->second(conn, message, receiveTime);
        }
        else
        {
            _defaultCallback(conn, message, receiveTime);
        }
    }

    void registerMessageCallback(google::protobuf::Descriptor const* desc,
                                 ProtobufMessageCallback const& callback)
    {
#ifndef TEST
        auto ret = _callbacks.insert(CallbackMap::value_type(desc , callback));
        if(ret.second == false)
            LOG_INFO << "failed to register callback";
#else
        _callbacks[desc] = callback;
#endif
    }

private:

    typedef std::map<google::protobuf::Descriptor const*, ProtobufMessageCallback> CallbackMap;
    CallbackMap _callbacks;
    ProtobufMessageCallback _defaultCallback;
};

#endif
