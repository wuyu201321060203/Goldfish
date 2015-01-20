#include "UserInfoService.h"

//token decode
//protobuf optional how to deal

void UserInfoService::onCreateInfo(TcpConnectionPtr const& conn,
                                   MessagePtr const& msg,
                                   muduo::Timestamp)
{
    boost::shared_ptr<CreateUserMsg> query = muduo::down_cast<CreateUserMsg>(msg);
    string tmp = msg->token();//decode
    Token token(tmp);
    if(token.niuXThanUser())
    {
        (g_Initializer.getThreadPool()).run(boost::bind(&doCreateUser , conn,
            domainName , groupName , userName , passwd , identity));
    }
    else
    {
        CreateUserACK reply;
        reply.set_statusCode();
        conn->send(reply);
    }
}

void UserInfoService::onDeleteInfo(TcpConnectionPtr const& conn,
                                   MessagePtr const& msg,
                                   muduo::Timestamp)
{
    boost::shared_ptr<DeleteUserMsg> query = muduo::down_cast<DeleteUserMsg>(msg);
    string tmp = msg->token();
    Token token(tmp);
    if(token.niuXThanUser())
    {
        (g_Initializer.getThreadPool()).run(boost::bind(&doDeleteUser , conn,
            userName));
    }
    else
    {
        DeleteUserACK reply;
        reply.set_statusCode();
        conn->send(reply);
    }
}

void UserInfoService::onUpdateInfo(TcpConnectionPtr const& conn,
                                   MessagePtr const& msg,
                                   muduo::Timestamp)
{
    boost::shared_ptr<UpdateUserMsg> query = muduo::down_cast<UpdateUserMsg>(msg);
    string tmp = msg->token();
    Token token(tmp);
    if(token.niuXThanGroupAdmin())
    {
        string oldUserName = msg->oldUserName();
        string newUserName = msg->newUserName();
        string domainName = msg->domainName();
        string groupName = msg->groupName();
        string passwd = msg->passwd();
        int32_t authority = msg->authority();
        (g_Initializer.getThreadPool()).run(boost::bind(&doUpdateGroup , conn,
            oldUserName , newUserName , domainName , groupName , passwd , authority));
    }
    else
    {
        UpdateUserACK reply;
        reply.set_statusCode();
        conn->send(reply);
    }
}

void UserInfoService::onGetInfo(TcpConnectionPtr const& conn,
                                MessagePtr const& msg,
                                muduo::Timestamp)
{
    boost::shared_ptr<GetUserInfoMsg> query = muduo::down_cast<GetUserInfoMsg>(msg);
    string userName = msg->userName();
    (g_Initializer.getThreadPool()).run(boost::bind(&doGetUserInfo , conn,
        userName));
}

void UserInfoService::doCreateUser(TcpConnectionPtr const& conn , string domainName,
                                   string groupName , string userName,
                                   string passwd , string authority)
{
    ConnectionPtr dbConn = SingleConnectionPool::instance().
                                    getConnection<MysqlConnection>();
    ResultPtr result = dbConn->executeQuery("select id from Domain where name = %s",
                                            domainName);
    CreateUserAck reply;
    if(result->next())
    {
        result = dbConn->executeQuery("select id from Group where name = %s",
                                        groupName);
        if(result->next())
        {
            dbConn->execute("inert into User values(%s , %s , %s , %s , %d)" , domainName,
                            groupName , userName , passwd , authority);
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

void UserInfoService::doDeleteUser(TcpConnectionPtr const& conn , string userName)
{
    ConnectionPtr dbConn = SingleConnectionPool::instance().
        getConnection<MysqlConnection>();

    DeleteUserAck reply;
    try
    {
        dbConn->execute("delete from User where userName = %s" , userName);
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

void UserInfoService::doUpdateUser(TcpConnectionPtr const& conn , string oldUserName,
                   string newUserName , string domain , string group,
                   string passwd , int authority)
{
    ConnectionPtr dbConn = SingleConnectionPool::instance().
        getConnection<MysqlConnection>();

    UpdateUserAck reply;
    try
    {
        dbConn->execute("update from User set name = %s , domain = %s,
                         group = %s , passwd = %s , authority = %d where name = %s",
                         newUserName , domain , group , passwd , authority , oldUserName);
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

void UserInfoService::doGetUserInfo(TcpConnectionPtr const& conn , string userName)
{
    ConnectionPtr dbConn = SingleConnectionPool::instance().
        getConnection<MysqlConnection>();

    GetUserInfoAck reply;
    try
    {
        ResultSetPtr result = dbConn->executeQuery(
                "select domain , group , passwd , authority from User where
                                                    userName = %s", userName);
        if(result->next())
        {
            reply->set_statusCode();
            string domain = result->getString(1);
            string group = result->getString(2);
            string passwd = result->getString(3);
            int32_t authority = result->getInt(4);
            reply->set_domain(domain);
            reply->set_domain(group);
            reply->set_domain(passwd);
            reply->set_domain(authority);
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