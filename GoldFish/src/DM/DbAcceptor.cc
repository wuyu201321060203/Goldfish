#include <boost/tokenizer.hpp>

#include "Config.h"
#include "DbAcceptor.h"

extern Initializer g_Initializer;

void DbAcceptor::onPreserve(TcpConnectionPtr const& conn,
                MessagePtr const& msg,
                muduo::Timestamp timeStamp)
{
    boost::shared_ptr<PreserveMsg> message =
                                    muduo::down_pointer_cast<PreserveMsg>(msg);
    string domain = message->domainName();
    ConnectionPtr dbConn = SingleConnectionPool::instance()
                                            .getConnection<MysqlConnection>();
    PreserveACKMsg replyMsg;
    replyMsg.set_statusCode(PRESERVE_FAIL);
    try
    {
        ResultPtr result = dbConn->executeQuery("select ip from DomainImportConfig where name = %s",
            domain.c_str());
        if(result)
        {
            if(result->next())
            {
                string ips = result->getStringByName(ip);
                int ipNum = message->domainName_size();
                for(int i = 0 ; i != ipNum ; ++i)
                {
                    ips += "#";
                    ips += message->get_domainName(i);
                }
                dbConn->execute("update DomainImportConfig SET ip = %s where name = %s",
                    ips , domain.c_str());
            }
            replyMsg.set_statusCode(SUCCESS);
            return;
        }
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

void DbAcceptor::onLoad(TcpConnectionPtr const& conn,
                        MessagePtr const& msg,
                        muduo::Timestamp timeStamp)
{
    boost::shared_ptr<LoadMsg> message =
                                    muduo::down_pointer_cast<LoadMsg>(msg);
    string domain = message->domainName();
    ConnectionPtr dbConn = SingleConnectionPool::instance()
                                            .getConnection<MysqlConnection>();
    LoadACKMsg replyMsg;
    replyMsg.set_statusCode(LOAD_FAIL);
    try
    {
        ResultPtr result = dbConn->executeQuery("select ips from DomainImportConfig where name = %s",
            domain.c_str());
        if(result)
        {
            string ips;
            if(result->next())
                ips = result->getStringByName(ip);
            typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
            boost::char_separator<char> sep("#");
            tokenizer tokens(s2, sep);
            int pos = 0;
            for(tokenizer::iterator tok_iter = tokens.begin() ;
                tok_iter != tokens.end() ; ++tok_iter , ++pos)
            {
                replyMsg.set_raIp(pos);
            }
            replyMsg.set_statusCode = SUCCESS;
        }
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