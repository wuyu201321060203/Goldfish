#include <string>

#include <DM/DbAcceptor.h>
#include <DM/Initializer.h>
#include <Db/ConnectionPool.h>
#include <Db/ResultSet.h>
#include <Db/Connection.h>
#include <Exception/SQLException.h>
#include <mysql/MysqlConnection.h>

#include <boost/bind.hpp>

#include <muduo/base/ThreadPool.h>

using OOzdb::ConnectionPool;

extern Initializer g_Initializer;
extern ConnectionPool g_DbPool;

#ifdef TEST
extern ConfigLookupACK tLookUpACK;
extern ConfigPersistenceACK tPreserveACK;
extern ConfigDeleteACK tDeleteACK;
#endif

using namespace muduo::net;
using namespace muduo;
using namespace OOzdb;

void DbAcceptor::onPreserve(TcpConnectionPtr const& conn,
                            MessagePtr const& msg,
                            Timestamp timeStamp)
{
    (g_Initializer.getThreadPool()).run( boost::bind(&DbAcceptor::doPreserve , this ,
                                         conn , msg , timeStamp) );
}

void DbAcceptor::onLoad(TcpConnectionPtr const& conn,
                        MessagePtr const& msg,
                        muduo::Timestamp timeStamp)
{
    (g_Initializer.getThreadPool()).run( boost::bind(&DbAcceptor::doLoad , this ,
                                         conn , msg , timeStamp) );
}

void DbAcceptor::onDelete(TcpConnectionPtr const& conn,
                          MessagePtr const& msg,
                          muduo::Timestamp timeStamp)
{
    (g_Initializer.getThreadPool()).run( boost::bind(&DbAcceptor::doDelete , this ,
                                         conn , msg , timeStamp) );
}

void DbAcceptor::doPreserve(TcpConnectionPtr const& conn,
                            MessagePtr const& msg,
                            Timestamp timeStamp)
{
    ConfigPersistenceMsgPtr message =
                            muduo::down_pointer_cast<ConfigPersistenceMsg>(msg);

    std::string domain = message->domainname();
    ConnectionPtr dbConn = g_DbPool.getConnection<MysqlConnection>();
    ConfigPersistenceACK reply;
    reply.set_statuscode(CONFIG_PRESERVE_FAIL);
    try
    {
        ResultSetPtr result =
            dbConn->executeQuery(" select id from DOMAIN_INFO where name = '%s' ",
                                 domain.c_str() );
        if(result->next())
        {
            int ipNum = message->raip_size();
            std::string ip;
            for(int i = 0 ; i != ipNum ; ++i)
            {
                ip = message->raip(i);
                dbConn->execute(
                    "insert into IMCONFIG_INFO (domainName , raIP) \
                     values ('%s' , '%s')" , domain.c_str() , ip.c_str() );
            }
            reply.set_statuscode(SUCCESS);
        }
    }
    catch(SQLException& e)
    {
#ifdef DEBUG
        LOG_INFO << e.getReason();
#endif
    }
#ifndef TEST
    (g_Initializer.getCodec()).send(conn , reply);
#endif

#ifdef TEST
    tPreserveACK = reply;
#endif
    dbConn->close();
}

void DbAcceptor::doLoad(TcpConnectionPtr const& conn,
                        MessagePtr const& msg,
                        muduo::Timestamp timeStamp)
{
    ConfigLookupMsgPtr message = muduo::down_pointer_cast<ConfigLookupMsg>(msg);
    std::string domain = message->domainname();
    ConnectionPtr dbConn = g_DbPool.getConnection<MysqlConnection>();
    ConfigLookupACK reply;
    reply.set_statuscode(DOMAIN_NO_CONFIG);
    try
    {
        ResultSetPtr result = dbConn->executeQuery("select raIP from \
            IMCONFIG_INFO where domainName = '%s' ", domain.c_str());
        std::string ip;
        while(result->next())
        {
            ip = result->getString(1);
            reply.add_raip(ip);
            reply.set_statuscode(SUCCESS);
        }
    }
    catch(SQLException& e)
    {
#ifdef DEBUG
        LOG_INFO << e.getReason();
#endif
        reply.set_statuscode(CONFIG_QUERY_FAIL);
    }
#ifndef TEST
    (g_Initializer.getCodec()).send(conn , reply);
#endif

#ifdef TEST
    tLookUpACK = reply;
#endif
    dbConn->close();
}

void DbAcceptor::doDelete(TcpConnectionPtr const& conn,
                          MessagePtr const& msg,
                          muduo::Timestamp timeStamp)
{
    ConfigDeleteMsgPtr message = muduo::down_pointer_cast<ConfigDeleteMsg>(msg);
    std::string domain = message->domainname();
    ConnectionPtr dbConn = g_DbPool.getConnection<MysqlConnection>();
    ConfigDeleteACK reply;
    reply.set_statuscode(CONFIG_DELETE_FAIL);
    try
    {
        dbConn->execute("delete from IMCONFIG_INFO where domainName = '%s' ",
                        domain.c_str());
        reply.set_statuscode(SUCCESS);
    }
    catch(SQLException& e)
    {
#ifdef DEBUG
        LOG_INFO << e.getReason();
#endif
    }
#ifndef TEST
    (g_Initializer.getCodec()).send(conn , reply);
#endif

#ifdef TEST
    tDeleteACK = reply;
#endif
    dbConn->close();
}