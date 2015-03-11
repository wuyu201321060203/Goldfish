#include <DM/DCRegister.h>
#include <DM/Initializer.h>
#include <DM/DMServer.h>

#include <Db/ConnectionPool.h>
#include <Db/ResultSet.h>
#include <mysql/MysqlConnection.h>
#include <Exception/SQLException.h>

using namespace OOzdb;
using namespace muduo;
using namespace muduo::net;

DCRegister::DCRegister(DMServer* dm):_dm(dm)
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
        this , conn , moduleID , ip , port) );
}

void DCRegister::doRegister(muduo::net::TcpConnectionPtr const& conn,
                            uint32_t moduleID , STDSTR ip , uint32_t port)
{
    ConnectionPtr dbConn = ( Initializer::getDbPool() ).
        getConnection<MysqlConnection>();

    RegisterMsgACK reply;
    reply.set_statuscode(SUCCESS);
    try
    {
        dbConn->execute("update DOMAIN_INFO set IP = '%s', Port = '%d' where \
            id = '%d'" , ip.c_str() , port , moduleID);
        ResultSetPtr ret = dbConn->executeQuery("select name from DOMAIN_INFO \
            where id = '%d'" , moduleID);
        if(ret->next())
            reply.set_domainname(ret->getString(1));
        else
            reply.set_domainname("UNKONWN-DOMAIN");
    }
    catch(SQLException const& e)
    {
#ifdef DMDEBUG
        LOG_INFO << "DC failed to register";
        reply.set_statuscode(UNKNOWN_SYSERROR);
#endif
    }
    dbConn->close();
#ifndef TEST
    (_dm->_dbInfoHandler)->addDCConn(conn);
    (_dm->_sysInfoHandler)->addDCConn(conn);
    (_dm->_dcManager).delegateTimerTask(2 , 10 , 3,
        boost::bind(&DMServer::onTimeout , _dm , _1) , conn);

    ( Initializer::getCodec()  ).send(conn , reply);
#endif
}