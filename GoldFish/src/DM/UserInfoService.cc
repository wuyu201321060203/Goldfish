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
#include <Exception/Exception.h>

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;
using boost::any_cast;

extern ConnectionPool g_DbPool;
typedef boost::shared_ptr<MutexLock> MutexLockPtr;

void UserInfoService::onCreateInfo(TcpConnectionPtr const& conn,
                                   MessagePtr const& msg,
                                   Timestamp)//client should assure this function works right
{
    UserCreateMsgPtr query = muduo::down_pointer_cast<UserCreateMsg>(msg);
    STDSTR tmp = query->token();
    Token token(tmp);
    if(token.niuXThanCommonUser())
    {
        STDSTR domainName = query->domainname();
        STDSTR groupName = query->groupname();
        STDSTR userName = query->username();
        STDSTR passwd = query->password();
        ulong authority = query->authority();
        (g_Initializer.getThreadPool()).run(boost::bind(&UserInfoService::doCreateUser,
            this , conn , domainName , groupName , userName , passwd , authority));
    }
    else
        onTokenFailAuthFailed<UserCreateACK>(conn);
}

void UserInfoService::onDeleteInfo(TcpConnectionPtr const& conn,
                                   MessagePtr const& msg,
                                   Timestamp)//client should assure this function works right
{
    UserDestroyMsgPtr query = muduo::down_pointer_cast<UserDestroyMsg>(msg);
    STDSTR tmp = query->token();
    Token token(tmp);
    if(token.niuXThanCommonUser())
    {
        STDSTR userName = query->username();
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
    (g_Initializer.getThreadPool()).run(boost::bind(&UserInfoService::doUpdateUser,
        this , conn , userName , passwd));
}

void UserInfoService::onGetInfo(TcpConnectionPtr const& conn,
                                MessagePtr const& msg,
                                Timestamp)
{
    UserInfoGetMsgPtr query = muduo::down_pointer_cast<UserInfoGetMsg>(msg);
    STDSTR tmp = query->token();
    Token token(tmp);
    (g_Initializer.getThreadPool()).run(boost::bind(&UserInfoService::doGetUserInfo,
                                        this , conn , token));
}

void UserInfoService::doCreateUser(TcpConnectionPtr const& conn , STDSTR domainName,
                                   STDSTR groupName , std::string userName,
                                   STDSTR passwd , ulong authority)
{
    ConnectionPtr dbConn = g_DbPool.getConnection<MysqlConnection>();
    ResultSetPtr result;
    UserCreateACK reply;
    try
    {
        {
            MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
            MutexLockGuard guard(**lock);
            result = dbConn->executeQuery("select id from DOMAIN_INFO \
                                    where name = '%s'" , domainName.c_str());
            if(result->next())
            {
                int domainID = result->getInt(1);
                result = dbConn->executeQuery("select id from GROUP_INFO where name = '%s'",
                    groupName.c_str());
                if(result->next())
                {
                    int groupID = result->getInt(1);
                    dbConn->execute("insert into USER_INFO(belong2Domain , belong2Group\
                        , name , passwd , identity) values('%d' , '%d' , '%s',\
                        '%s' , '%d')" , domainID , groupID,
                        userName.c_str() , passwd.c_str() , authority);
                    reply.set_statuscode(SUCCESS);
                }
                else
                    reply.set_statuscode(UNEXISTED_GROUP);
            }
            else
                reply.set_statuscode(UNEXISTED_DOMAIN);
        }
    }
    catch(SQLException const& e)
    {
#ifdef TEST
         std::cout << e.getReason() << "\n";
#endif
         reply.set_statuscode(UNKNOWN_SYSERROR);
    }
    dbConn->close();
#ifndef TEST
    ( g_Initializer.getCodec() ).send(conn , reply);
#endif
}

void UserInfoService::doDeleteUser(TcpConnectionPtr const& conn , STDSTR userName)
{
    ConnectionPtr dbConn = g_DbPool.getConnection<MysqlConnection>();
    ResultSetPtr result;
    UserDestroyACK reply;
    try
    {
        {
            MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
            MutexLockGuard guard(**lock);
            result = dbConn->executeQuery("select id from USER_INFO\
                                        where name = '%s'" , userName.c_str());
            if(result->next())
            {
                dbConn->executeQuery("delete from USER_INFO where name = '%s'",
                                                    userName.c_str());
                reply.set_statuscode(SUCCESS);
            }
            else
                reply.set_statuscode(UNEXISTED_USER);
        }
    }
    catch(SQLException const& e)
    {
#ifdef TEST
         std::cout << e.getReason() << "\n";
#endif
         reply.set_statuscode(UNKNOWN_SYSERROR);
    }
    dbConn->close();
#ifndef TEST
    ( g_Initializer.getCodec() ).send(conn , reply);
#endif
}

void UserInfoService::doUpdateUser(TcpConnectionPtr const& conn , STDSTR userName,
                                   STDSTR passwd)
{
    ConnectionPtr dbConn = g_DbPool.getConnection<MysqlConnection>();
    ResultSetPtr result;
    UserInfoUpdateACK reply;
    try
    {
        {
            MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
            MutexLockGuard guard(**lock);
            result = dbConn->executeQuery("select id from USER_INFO\
                where name = '%s'" , userName.c_str());
            if(result->next())
            {
                dbConn->executeQuery("update USER_INFO set passwd = '%s' where name = '%s'",
                    passwd.c_str() , userName.c_str());
                reply.set_statuscode(SUCCESS);
            }
            else
                reply.set_statuscode(UNEXISTED_USER);
        }
    }
    catch(SQLException const& e)
    {
#ifdef TEST
        std::cout << e.getReason() << "\n";
#endif
        reply.set_statuscode(UNKNOWN_SYSERROR);
    }
    dbConn->close();
#ifndef TEST
    ( g_Initializer.getCodec() ).send(conn , reply);
#endif
}

void UserInfoService::doGetUserInfo(TcpConnectionPtr const& conn , Token token)
{
    typedef MSG_DM_CLIENT_USER_INFO_GET_ACK_USER_INFO UserInfo;
    ConnectionPtr dbConn = g_DbPool.getConnection<MysqlConnection>();
    ResultSetPtr result;
    UserInfoGetACK reply;
    STDSTR prefix("select passwd , belong2Domain , belong2Group , identity\
                    from USER_INFO");
    STDSTR sqlQuery(prefix);

    try
    {
        if(token.niuXThanDomainAdmin())
        {
        }
        else if(token.niuXThanGroupAdmin())
        {
            result = dbConn->executeQuery("select id from DOMAIN_INFO where name = '%s'",
                                            (token.getDomain()).c_str());
            if(result->next())
                sqlQuery += ( " where belong2Domain = " + result->getInt(1) );
            else
                THROW(SQLException , "illegal token with a unexisted domain");
        }
        else if(token.niuXThanCommonUser())
        {
            result = dbConn->executeQuery("select id from GROUP_INFO where name = '%s'",
                                            (token.getGroup()).c_str());
            if(result->next())
                sqlQuery += ( " where belong2Group = " + result->getInt(1) );
            else
                THROW(SQLException , "illegal token with a unexisted group");
        }
        else
        {
            result = dbConn->executeQuery("select id from USER_INFO where name = '%s'",
                                                (token.getUserName()).c_str());
            if(result->next())
                sqlQuery += ( " where name = " + token.getUserName() );//no measure to deal the same name
            else
                THROW(SQLException , "illegal token with a unexisted user");

        }
        {
            MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
            MutexLockGuard guard(**lock);
            result = dbConn->executeQuery(sqlQuery.c_str());
            UserInfo* info = NULL;
            STDSTR domainName;
            STDSTR groupName;
            STDSTR userName(token.getUserName());
            STDSTR password;
            ulong  identity;
            ResultSetPtr tmp;
            while(result->next())
            {
                reply.set_statuscode(SUCCESS);
                info = reply.add_userinfo();
                tmp = dbConn->executeQuery("select name from DOMAIN_INFo where id = '%d'",
                                            result->getInt(2));
                if(tmp->next())
                    domainName = tmp->getString(1);
                else
                    THROW(SQLException , "unexisted domain");
                tmp = dbConn->executeQuery("select name from GROUP_INFo where id = '%d'",
                                            result->getInt(3));
                if(tmp->next())
                    groupName = tmp->getString(1);
                else
                    THROW(SQLException , "unexisted group");

                info->set_domainname(domainName);
                info->set_groupname(groupName);
                info->set_username(userName);
                info->set_password(result->getString(1));
                info->set_authority(result->getInt(4));
            }
        }
    }
    catch(SQLException const& e)
    {
#ifdef TEST
        std::cout << e.getReason() << "\n";
#endif
        reply.set_statuscode(UNKNOWN_SYSERROR);
    }
    dbConn->close();
#ifndef TEST
    ( g_Initializer.getCodec() ).send(conn , reply);
#endif
}