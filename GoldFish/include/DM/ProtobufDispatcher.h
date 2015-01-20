#ifndef DISPATCHER_LITE_H
#define DISPATCHER_LITE_H

#include <muduo/net/Callbacks.h>

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
        : defaultCallback_(defaultCb)
    {
    }

    void onProtobufMessage(muduo::net::TcpConnectionPtr const& conn,
                           MessagePtr const& message,
                           muduo::Timestamp receiveTime) const
    {
        CallbackMap::const_iterator it = callbacks_.find(message->GetDescriptor());
        if (it != callbacks_.end())
        {
            it->second(conn, message, receiveTime);
        }
        else
        {
            defaultCallback_(conn, message, receiveTime);
        }
    }

    void registerMessageCallback(google::protobuf::Descriptor const* desc,
                                 ProtobufMessageCallback const& callback)
    {
        callbacks_[desc] = callback;
    }

private:

    typedef std::map<google::protobuf::Descriptor const*, ProtobufMessageCallback> CallbackMap;
    CallbackMap callbacks_;
    ProtobufMessageCallback defaultCallback_;
};

#endif
