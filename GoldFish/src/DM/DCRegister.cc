#include <DM/DCRegister.h>
#include <DM/Initializer.h>

#include <Db/ConnectionPool.h>
#include <Db/ResultSet.h>
#include <mysql/MysqlConnection.h>
#include <Exception/SQLException.h>

using namespace OOzdb;
using namespace muduo;
using namespace muduo::net;

DCRegister::DCRegister()
{
    ( Initializer::getDispatcher() ).registerMessageCallback(
        RegisterMsg::descriptor(),
        boost::bind(&DCRegister::onMessage , this , _1 , _2 , _3)
        );
}

void DCRegister::onMessage(muduo::net::TcpConnectionPtr const& conn,
                           MessagePtr const& msg,
                           muduo::Timestamp receiveTime)
{
    RegisterMsgPtr apply = muduo::down_pointer_cast<RegisterMsg>(msg);
    STDSTR ip = apply->ip();
    uint32_t port = apply->port();
    uint32_t moduleID = apply->moduleid();

    ( Initializer::getThreadPool() ).run( boost::bind(&DCRegister::doRegister,
        this , moduleID , ip , port) );
}

void DCRegister::doRegister(uint32_t moduleID , STDSTR ip , uint32_t port)
{
    ConnectionPtr dbConn = ( Initializer::getDbPool() ).
        getConnection<MysqlConnection>();

    RegisterMsgACK reply;
    reply.set_statuscode(SUCCESS);
    try
    {
        dbConn->execute("update DOMAIN_INFO set IP = '%s', Port = '%d' where \
            id = '%d'" , ip.c_str() , port , moduleID);
    }
    catch(SQLException const& e)
    {
#ifdef DEBUG
        LOG_INFO << "DC failed to register";
        reply.set_statuscode(UNKNOWN_SYSERROR);
#endif
    }
    dbConn->close();
#ifndef TEST
    ( Initializer::getCodec()  ).send(conn , reply);
#endif
}