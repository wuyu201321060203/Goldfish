#include <string>

#ifdef TEST
#include <vector>
#endif

#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#ifdef DMDEBUG
#include <muduo/base/Logging.h>
#endif
#include <muduo/base/Types.h>
#include <muduo/base/ThreadPool.h>

#include <DM/UserInfoService.h>
#include <DM/Token.h>
#include <DM/Initializer.h>

#include <Db/ResultSet.h>
#include <Db/ConnectionPool.h>
#include <mysql/MysqlConnection.h>
#include <Exception/SQLException.h>
#include <Exception/Exception.h>

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;
using boost::any_cast;

#ifdef TEST
typedef MSG_DM_CLIENT_USER_INFO_GET_ACK_USER_INFO UserInfo;
extern std::vector<UserInfo> testArray1;
#endif

UserInfoService::UserInfoService()
{
    ( Initializer::getDispatcher() ).registerMessageCallback(
        UserCreateMsg::descriptor(),
        boost::bind(&UserInfoService::onCreateInfo , this , _1 , _2 , _3)
    );

    ( Initializer::getDispatcher() ).registerMessageCallback(
        UserDestroyMsg::descriptor(),
        boost::bind(&UserInfoService::onDeleteInfo , this , _1 , _2 , _3)
    );

    ( Initializer::getDispatcher() ).registerMessageCallback(
        UserInfoUpdateMsg::descriptor(),
        boost::bind(&UserInfoService::onUpdateInfo , this , _1 , _2 , _3)
    );

    ( Initializer::getDispatcher() ).registerMessageCallback(
        UserInfoGetMsg::descriptor(),
        boost::bind(&UserInfoService::onGetInfo , this , _1 , _2 , _3)
    );
}

void UserInfoService::onCreateInfo(TcpConnectionPtr const& conn,
                                   MessagePtr const& msg,
                                   Timestamp)//client should assure this function works right
{
    UserCreateMsgPtr query = muduo::down_pointer_cast<UserCreateMsg>(msg);
    STDSTR tmp = query->token();
#ifndef TEST
    ( Initializer::getDesEcbAcceptor() )->decode(tmp);
#endif
    Token token(tmp);
    if(token.niuXThanCommonUser())
    {
        STDSTR domainName = query->domainname();
        STDSTR groupName = query->groupname();
        STDSTR userName = query->username();
        STDSTR passwd = query->password();
        ulong authority = query->authority();
        (Initializer::getThreadPool()).run(boost::bind(&UserInfoService::doCreateUser,
            this , conn , domainName , groupName , userName , passwd , authority));
    }
    else
        onTokenAuthFailed<UserCreateACK>(conn);
}

void UserInfoService::onDeleteInfo(TcpConnectionPtr const& conn,
                                   MessagePtr const& msg,
                                   Timestamp)//client should assure this function works right
{
    UserDestroyMsgPtr query = muduo::down_pointer_cast<UserDestroyMsg>(msg);
    STDSTR tmp = query->token();
#ifndef TEST
    ( Initializer::getDesEcbAcceptor() )->decode(tmp);
#endif
    Token token(tmp);
    if(token.niuXThanCommonUser())
    {
        STDSTR userName = query->username();
        (Initializer::getThreadPool()).run(boost::bind(&UserInfoService::doDeleteUser,
            this , conn , userName));
    }
    else
        onTokenAuthFailed<UserDestroyACK>(conn);
}

void UserInfoService::onUpdateInfo(TcpConnectionPtr const& conn,
                                   MessagePtr const& msg,
                                   Timestamp)
{
    UserInfoUpdateMsgPtr query = muduo::down_pointer_cast<UserInfoUpdateMsg>(msg);
    STDSTR tmp = query->token();
#ifndef TEST
    ( Initializer::getDesEcbAcceptor() )->decode(tmp);
#endif
    Token token(tmp);
    STDSTR userName = token.getUserName();
    STDSTR passwd = query->password();
    (Initializer::getThreadPool()).run(boost::bind(&UserInfoService::doUpdateUser,
        this , conn , userName , passwd));
}

void UserInfoService::onGetInfo(TcpConnectionPtr const& conn,
                                MessagePtr const& msg,
                                Timestamp)
{
    UserInfoGetMsgPtr query = muduo::down_pointer_cast<UserInfoGetMsg>(msg);
    STDSTR tmp = query->token();
#ifndef TEST
    ( Initializer::getDesEcbAcceptor() )->decode(tmp);
#endif
    Token token(tmp);
    (Initializer::getThreadPool()).run(boost::bind(&UserInfoService::doGetUserInfo,
                                        this , conn , token));
}

void UserInfoService::doCreateUser(TcpConnectionPtr const& conn , STDSTR domainName,
                                   STDSTR groupName , std::string userName,
                                   STDSTR passwd , ulong authority)
{
    ConnectionPtr dbConn = Initializer::getDbPool().getConnection<MysqlConnection>();
    ResultSetPtr result;
    UserCreateACK reply;
    int domainID = ROOT_DOMAIN;
    int groupID = ROOT_DOMAINADMIN_GROUP;
    int executeFlag = 1;
    try
    {
        if("*" != domainName)
        {
            result = dbConn->executeQuery("select id from DOMAIN_INFO \
                where name = '%s'" , domainName.c_str());

            if(result->next())
                domainID = result->getInt(1);
            else
            {
                reply.set_statuscode(UNEXISTED_DOMAIN);
                executeFlag = 0;
            }
        }
        if("*" != groupName)
        {
            result = dbConn->executeQuery("select id from GROUP_INFO where name = '%s'",
                groupName.c_str());

            if(result->next())
                groupID = result->getInt(1);
            else
            {
                reply.set_statuscode(UNEXISTED_GROUP);
                executeFlag = 0;
            }
        }
        if(executeFlag)
        {
            dbConn->execute("insert into USER_INFO(belong2Domain , belong2Group \
                , name , passwd , identity) values('%d' , '%d' , '%s',\
                    '%s' , '%d')" , domainID , groupID , userName.c_str(),
                passwd.c_str() , authority);

            reply.set_statuscode(SUCCESS);
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
    ( Initializer::getCodec() ).send(conn , reply);
#endif
}

void UserInfoService::doDeleteUser(TcpConnectionPtr const& conn , STDSTR userName)
{
    ConnectionPtr dbConn = Initializer::getDbPool().getConnection<MysqlConnection>();
    //ResultSetPtr result;
    UserDestroyACK reply;
    try
    {
        //{
        //MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
        //MutexLockGuard guard(**lock);
        ResultSetPtr result = dbConn->executeQuery("select id from USER_INFO\
            where name = '%s'" , userName.c_str());
        if(result->next())
        {
            dbConn->execute("delete from USER_INFO where name = '%s'",
                userName.c_str());
            reply.set_statuscode(SUCCESS);
        }
        else
            reply.set_statuscode(UNEXISTED_USER);
        //}
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
    ( Initializer::getCodec() ).send(conn , reply);
#endif
}

void UserInfoService::doUpdateUser(TcpConnectionPtr const& conn , STDSTR userName,
                                   STDSTR passwd)
{
    ConnectionPtr dbConn = Initializer::getDbPool().getConnection<MysqlConnection>();
    //ResultSetPtr result;
    UserInfoUpdateACK reply;
    try
    {
        //{
        //MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
        //MutexLockGuard guard(**lock);
        ResultSetPtr result = dbConn->executeQuery("select id from USER_INFO\
            where name = '%s'" , userName.c_str());
        if(result->next())
        {
            dbConn->execute("update USER_INFO set passwd = '%s' where name = '%s'",
                passwd.c_str() , userName.c_str());
            reply.set_statuscode(SUCCESS);
        }
        else
            reply.set_statuscode(UNEXISTED_USER);
        //}
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
    ( Initializer::getCodec() ).send(conn , reply);
#endif
}

void UserInfoService::doGetUserInfo(TcpConnectionPtr const& conn , Token token)
{
    typedef MSG_DM_CLIENT_USER_INFO_GET_ACK_USER_INFO UserInfo;
    ConnectionPtr dbConn = Initializer::getDbPool().getConnection<MysqlConnection>();
    ConnectionPtr dbConn1 = Initializer::getDbPool().getConnection<MysqlConnection>();
    ResultSetPtr result;
    UserInfoGetACK reply;
    STDSTR prefix("select passwd , belong2Domain , belong2Group , identity , name from USER_INFO ");
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
                sqlQuery += ( " where belong2Domain = " +
                    boost::lexical_cast<STDSTR>( result->getInt(1) ) );
            else
                THROW(SQLException , "illegal token with a unexisted domain");
        }
        else if(token.niuXThanCommonUser())
        {
            result = dbConn->executeQuery("select id from GROUP_INFO where name = '%s'",
                (token.getGroup()).c_str());
            if(result->next())
                sqlQuery += ( " where belong2Group = " +
                    boost::lexical_cast<STDSTR>( result->getInt(1) ) );
            else
                THROW(SQLException , "illegal token with a unexisted group");
        }
        else
        {
            result = dbConn->executeQuery("select id from USER_INFO where name = '%s'",
                (token.getUserName()).c_str());
            if(result->next())
                sqlQuery += ( " where name = '" + token.getUserName() +"'" );//no measure to deal the same name
            else
                THROW(SQLException , "illegal token with a unexisted user");

        }
        //{
        //MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
        //MutexLockGuard guard(**lock);
        result = dbConn->executeQuery(sqlQuery.c_str());
        UserInfo* info = NULL;
        STDSTR domainName;
        STDSTR groupName;
        int tmpDomainID;
        int tmpGroupID;
        ResultSetPtr tmp;
        while( result->next() )
        {
            reply.set_statuscode(SUCCESS);
            tmpDomainID = result->getInt(2);
            tmpGroupID = result->getInt(3);
            tmp = dbConn1->executeQuery("select name from DOMAIN_INFO where id = '%d'",
                tmpDomainID);
            if(tmp->next())
                domainName = tmp->getString(1);
            else
            {
                if( 0 == tmpDomainID )
                    domainName = "*";
                else
                    THROW(SQLException , "unexisted domain");
            }
            tmp = dbConn1->executeQuery("select name from GROUP_INFO where id = '%d'",
                tmpGroupID);
            if(tmp->next())
                groupName = tmp->getString(1);
            else
            {
                if( 0 == tmpGroupID )
                    groupName = "*";
                else
                    THROW(SQLException , "unexisted group");
            }

            info = reply.add_userinfo();
            info->set_domainname(domainName);
            info->set_groupname(groupName);
            info->set_username(result->getString(5));
            info->set_password(result->getString(1));
            info->set_authority(result->getInt(4));
#ifdef TEST
            testArray1.push_back(*info);
#endif
        }
        //}
    }
    catch(SQLException const& e)
    {
#ifdef TEST
        std::cout << e.getReason() << "\n";
#endif
        reply.set_statuscode(UNKNOWN_SYSERROR);
    }
    dbConn->close();
    dbConn1->close();
#ifndef TEST
    ( Initializer::getCodec() ).send(conn , reply);
#endif
}