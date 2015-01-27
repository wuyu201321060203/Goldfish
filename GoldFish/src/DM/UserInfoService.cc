#include <string>

#include <boost/any.hpp>
#include <muduo/base/Logging.h>
#include <muduo/base/Types.h>
#include <muduo/base/Mutex.h>
#include <muduo/base/ThreadPool.h>

#include <DM/UserInfoService.h>
#include <DM/Token.h>

#include <Db/ResultSet.h>
#include <Db/ConnectionPool.h>
#include <mysql/MysqlConnection.h>
#include <Exception/SQLException.h>

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;
using boost::any_cast;

extern ConnectionPool g_DbPool;
typedef boost::shared_ptr<MutexLock> MutexLockPtr;

void UserInfoService::onCreateInfo(TcpConnectionPtr const& conn,
                                   MessagePtr const& msg,
                                   Timestamp)
{
    UserCreateMsgPtr query = muduo::down_pointer_cast<UserCreateMsg>(msg);
    STDSTR tmp = query->token();
    Token token(tmp);
    if(token.niuXThanCommonUser())
    {
        STDSTR domainName = query->domainname();
        STDSTR groupName = query->groupname();
        STDSTR userName = query->username();
        STDSTR passwd = query->passwd();
        ulong authority = query->authority();
        (g_Initializer.getThreadPool()).run(boost::bind(&UserInfoService::doCreateUser,
            this , conn , domainName , groupName , userName , passwd , authority));
    }
    else
        onTokenFailAuthFailed<UserCreateACK>(conn);
}

void UserInfoService::onDeleteInfo(TcpConnectionPtr const& conn,
                                   MessagePtr const& msg,
                                   Timestamp)
{
    UserDestroyMsgPtr query = muduo::down_pointer_cast<UserDestroyMsg>(msg);
    STDSTR tmp = query->token();
    Token token(tmp);
    if(token.niuXThanCommonUser())
    {
        (g_Initializer.getThreadPool()).run(boost::bind(&UserInfoService::doDeleteUser,
            this , conn , userName));
    }
    else
        onTokenFailAuthFailed<UserDestroyACK>(conn);
}

void UserInfoService::onUpdateInfo(TcpConnectionPtr const& conn,
                                   MessagePtr const& msg,
                                   Timestamp)
{
    UserInfoUpdateMsgPtr query = muduo::down_pointer_cast<UserInfoUpdateMsg>(msg);
    STDSTR tmp = query->token();
    Token token(tmp);
    STDSTR userName = token.getUserName();
    STDSTR passwd = query->password();
    (g_Initializer.getThreadPool()).run(boost::bind(&UserInfoService::doUpdateGroup,
        this , conn , userName , passwd));
}

void UserInfoService::onGetInfo(TcpConnectionPtr const& conn,
                                MessagePtr const& msg,
                                Timestamp)
{
    UserInfoGetMsgPtr query = muduo::down_pointer_cast<UserInfoGetMsg>(msg);
    STDSTR tmp = query->token();
    Token token(tmp);
    STDSTR userName = token.getUserName();
    (g_Initializer.getThreadPool()).run(boost::bind(&UserInfoService::doGetUserInfo,
                                        this , conn , userName));
}

void UserInfoService::doCreateUser(TcpConnectionPtr const& conn , STDSTR domainName,
                                   STDSTR groupName , std::string userName,
                                   STDSTR passwd , ulong authority)
{
    ConnectionPtr dbConn = g_DbPool.getConnection<MysqlConnection>();
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

void UserInfoService::doDeleteUser(TcpConnectionPtr const& conn , STDSTR userName)
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

void UserInfoService::doUpdateUser(TcpConnectionPtr const& conn , STDSTR userName,
                                   STDSTR passwd)
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