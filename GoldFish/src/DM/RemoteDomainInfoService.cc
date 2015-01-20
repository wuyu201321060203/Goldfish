#include "RemoteDomainInfoService.h"


void RemoteDomainInfoService::onCreateInfo(TcpConnectionPtr const& conn,
                                           MessagePtr const& msg,
                                           muduo::Timestamp)
{
    boost::shared_ptr<CreateDomainMsg> query = muduo::down_cast<CreateDomainMsg>(msg);
    Token token(query->token());
    if(token.niuXThanDomainAdmin())
    {
        _resManager->applyResource(msg , conn);
    }
    else
    {
        CreateDomainACK reply;
        reply.set_statusCode();
        conn->send(reply);
    }
}

void RemoteDomainInfoService::onDeleteInfo(TcpConnectionPtr const& conn,
                                           MessagePtr const& msg,
                                           muduo::Timestamp)
{
    boost::shared_ptr<DeleteDomainMsg> query = muduo::down_cast<DeleteDomainMsg>(msg);
    Token token(query->token());
    if(token.niuXThanDomainAdmin())
    {
        _resManager->revokeResource(msg , conn);
    }
    else
    {
        DeleteDomainACK reply;
        reply.set_statusCode();
        conn->send(reply);
    }
}

void RemoteDomainInfoService::onUpdateInfo(TcpConnectionPtr const& conn,
                                           MessagePtr const& msg,
                                           muduo::Timestamp)
{
    boost::shared_ptr<UpdateDomainMsg> query = muduo::down_cast<UpdateDomainMsg>(msg);
    Token token(query->token());
    UpdateDomainACK reply;
    if(token.niuXThanDomainAdmin())
    {
        ConnectionPtr dbConn = SingleConntionPool::instance().getConnection<
            MysqlConnection>();
        string domainName = query->domainName();
        string description = query->description();
        dbConn->execute("update Domain set description = %s where name = %s",
                        description , domainName);
        reply.set_statusCode();

    }
    else
    {
        reply.set_statusCode();
    }
    conn->send(reply);
}

void RemoteDomainInfoService::onGetInfo(TcpConnectionPtr const& conn,
                                        MessagePtr const& msg,
                                        muduo::Timestamp)
{
    boost::shared_ptr<GetDomainMsg> query = muduo::down_cast<GetDomainMsg>(msg);
    Token token(query->token());
    GetDomainACK reply;
    if(token.niuXThanGroupAdmin())
    {
        ConnectionPtr dbConn = SingleConntionPool::instance().getConnection<
            MysqlConnection>();
        int domainNum = query->domainName_size();
        string domainName;
        string description;
        for(int i = 0 ; i != domainNum ; ++i)
        {
            domainName = query->domainName(i);
            ResultPtr result = dbConn->executeQuery("select description from
                        Domain where name = %s" , domainName);
            if(result->next())
            {
                description = result->getString(1);
                reply.set_domainInfo(domainName , description);
            }
            else
            {
                reply.set_statusCode();
                break;
            }
        }
    }
    else
    {
        reply.set_statusCode();
    }
    conn->send(reply);
}

ResManagerPtr getResManager()
{
    return _resManager;
}