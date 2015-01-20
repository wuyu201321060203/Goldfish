#include "GroupInfoService.h"

void GroupInfoService::onCreateInfo(TcpConnectionPtr const& conn,
                                    MessagePtr const& msg,
                                    muduo::Timestamp)
{
    boost::shared_ptr<CreateGroupMsg> query = muduo::down_cast<CreateGroupMsg>(msg);
    string tmp = msg->token();
    Token token(tmp);
    if(token.niuXThanGroupAdmin())
    {
        (g_Initializer.getThreadPool()).run(boost::bind(&doCreateGroup , conn,
                        groupName , belong2Domain , description));
    }
    else
    {
        CreateGroupACK reply;
        reply.set_statusCode();
        conn->send(reply);
    }
}

void GroupInfoService::onDeleteInfo(TcpConnectionPtr const&,
                                    MessagePtr const&,
                                    muduo::Timestamp)
{
    boost::shared_ptr<DeleteGroupMsg> query = muduo::down_cast<DeleteGroupMsg>(msg);
    string tmp = msg->token();
    Token token(tmp);
    if(token.niuXThanGroupAdmin())
    {
        (g_Initializer.getThreadPool()).run(boost::bind(&doDeleteGroup , conn,
            groupName));
    }
    else
    {
        DeleteGroupACK reply;
        reply.set_statusCode();
        conn->send(reply);
    }
}

void GroupInfoService::onUpdateInfo(TcpConnectionPtr const&,
                                    MessagePtr const&,
                                    muduo::Timestamp)
{
    boost::shared_ptr<UpdateGroupMsg> query = muduo::down_cast<UpdateGroupMsg>(msg);
    string tmp = msg->token();
    Token token(tmp);
    if(token.niuXThanGroupAdmin())
    {
        string descritpion = msg->groupDescription();
        (g_Initializer.getThreadPool()).run(boost::bind(&doUpdateGroup , conn,
            groupName , description));
    }
    else
    {
        UpdateGroupACK reply;
        reply.set_statusCode();
        conn->send(reply);
    }
}

void GroupInfoService::onGetInfo(TcpConnectionPtr const&,
                                 MessagePtr const&,
                                 muduo::Timestamp)
{
    boost::shared_ptr<GetGroupMsg> query = muduo::down_cast<GetGroupMsg>(msg);
    string tmp = msg->token();
    Token token(tmp);
    if(token.niuXThanGroupAdmin())
    {
        string groupName = msg->groupName();
        (g_Initializer.getThreadPool()).run(boost::bind(&doGetGroup , conn,
            groupName));
    }
    else
    {
        GetGroupACK reply;
        reply.set_statusCode();
        conn->send(reply);
    }
}

void doCreateGroup(TcpConnectionPtr const& conn , string groupName , string domain,
                   string description)
{
    ConnectionPtr dbConn = SingleConnectionPool::instance().
                                    getConnection<MysqlConnection>();
    ResultPtr result = dbConn->executeQuery("select id from Domain where name = %s",
                                            domain);
    CreateGroupAck reply;
    if(result->next())
    {
        result = dbConn->executeQuery("select id from Group where name = %s",
                                        groupName);
        if(!result->next())
        {
            dbConn->execute("inert into Group values(%s , %s , %s)" , groupName,
                            domain , description);
            reply->set_statusCode();
        }
        else
        {
            reply->set_statusCode();
        }
    }
    else
    {
        reply->set_statusCode();
    }
    dbConn->close();
    conn->send(reply);
}

void doDeleteGroup(TcpConnectionPtr const& conn , string groupName)
{
    ConnectionPtr dbConn = SingleConnectionPool::instance().
        getConnection<MysqlConnection>();

    DeleteGroupAck reply;
    try
    {
        dbConn->execute("delete from Group where groupName = %s" , groupName);
        reply->set_statusCode();
    }
    catch(SQLException const& e)
    {
#ifdef DEBUG
        LOG_INFO <<;
#endif
        reply->set_statusCode();

    }
    dbConn->close();
    conn->send(reply);
}

void doUpdateGroup(TcpConnectionPtr const& conn , string groupName,
                   string description)
{
    ConnectionPtr dbConn = SingleConnectionPool::instance().
        getConnection<MysqlConnection>();

    UpdateGroupAck reply;
    try
    {
        dbConn->execute("update from Group set description = %s where groupName = %s",
                        description , groupName);
        reply->set_statusCode();
    }
    catch(SQLException const& e)
    {
#ifdef DEBUG
        LOG_INFO <<;
#endif
        reply->set_statusCode();

    }
    dbConn->close();
    conn->send(reply);
}

void doGetGroup(TcpConnectionPtr const& conn , string groupName)
{
    ConnectionPtr dbConn = SingleConnectionPool::instance().
        getConnection<MysqlConnection>();

    GetGroupAck reply;
    try
    {
        ResultSetPtr result = dbConn->executeQuery(
                "select description from Group groupName = %s", groupName);
        if(result->next())
        {
            reply->set_statusCode();
            string des = result->getString(1);
            reply->set_description(des);
        }
        else
        {
            reply->set_statusCode();
        }
    }
    catch(SQLException const& e)
    {
#ifdef DEBUG
        LOG_INFO <<;
#endif
        reply->set_statusCode();

    }
    dbConn->close();
    conn->send(reply);
}