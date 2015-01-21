#include <string>

#include <boost/tokenizer.hpp>

#include <DM/DbAcceptor.h>
#include <Db/ConnectionPool.h>
#include <Db/ResultSet.h>
#include <mysql/MysqlConnection.h>

using OOzdb::ConnectionPool;

extern Initializer g_Initializer;
extern ConnectionPool g_DbPool;

using namespace muduo::net;
using namespace muduo;
using std::string;

void DbAcceptor::onPreserve(TcpConnectionPtr const& conn,
                            MessagePtr const& msg,
                            Timestamp timeStamp)
{
    ConfigPersistenceMsgPtr message =
                            muduo::down_pointer_cast<ConfigPersistenceMsg>(msg);

    string domain = message->domainname();
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
            string ip;
            for(int i = 0 ; i != ipNum ; ++i)
            {
                ip = message->raip(i);
                dbConn->execute(
                    "insert into IMCONFIG_INFO (domainName , raIP) \
                     values ('%s' , '%s')" , domain , ip );
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
    dbConn->send(reply);
    dbConn->close();
}

void DbAcceptor::onLoad(TcpConnectionPtr const& conn,
                        MessagePtr const& msg,
                        muduo::Timestamp timeStamp)
{
    ConfigLookupMsgPtr message = muduo::down_pointer_cast<ConfigLookupMsg>(msg);
    string domain = message->domainname();
    ConnectionPtr dbConn = g_DbPool.getConnection<MysqlConnection>();
    ConfigLookupACK reply;
    reply.set_statuscode(DOMAIN_NO_CONFIG);
    try
    {
        ResultSetPtr result = dbConn->executeQuery("select raIP from \
            IMConfig_INFO where domainName = '%s' ", domain.c_str());
        string ip;
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
    dbConn->send(reply);
    dbConn->close();
}

void DbAcceptor::onDelete(TcpConnectionPtr const& conn,
                          MessagePtr const& msg,
                          muduo::Timestamp timeStamp)
{
    boost::shared_ptr<DeleteMsg> message =
        muduo::down_pointer_cast<DeleteMsg>(msg);
    string domain = message->domainName();
    ConnectionPtr dbConn = SingleConnectionPool::instance()
        .getConnection<MysqlConnection>();
    DeleteACKMsg replyMsg;
    replyMsg.set_statusCode(DELETE_FAIL);
    try
    {
        ResultPtr result = dbConn->executeQuery("delete from DomainImportConfig where name = %s ",
            domain.c_str());
        if(result)
            replyMsg.set_statusCode = SUCCESS;
    }
    catch(SQLException& e)
    {
#ifdef DEBUG
        LOG_INFO << e.getReason();
#endif
    }
    dbConn->send(replyMsg);
    dbConn->close();
}