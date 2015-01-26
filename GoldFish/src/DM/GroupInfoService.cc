#include <string>

#include <boost/any.hpp>

#include <muduo/base/Logging.h>
#include <muduo/base/Types.h>
#include <muduo/base/Mutex.h>
#include <muduo/base/ThreadPool.h>

#include <DM/GroupInfoService.h>
#include <DM/Initializer.h>
#include <DM/Token.h>

#include <Db/ResultSet.h>
#include <Db/ConnectionPool.h>
#include <mysql/MysqlConnection.h>
#include <Exception/SQLException.h>

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;
using boost::any_cast;

extern Initializer g_Initializer;
extern ConnectionPool g_DbPool;

typedef boost::shared_ptr<MutexLock> MutexLockPtr;

void GroupInfoService::onCreateInfo(TcpConnectionPtr const& conn,
                                    MessagePtr const& msg,
                                    Timestamp time)
{
    GroupCreateMsgPtr query = muduo::down_pointer_cast<GroupCreateMsg>(msg);
    std::string tmp = query->token();
    Token token(tmp);
    if(token.niuXThanGroupAdmin())
    {
        std::string groupName = query->groupname();
        std::string belong2Domain = query->belong2domain();
        std::string description = query->groupdescription();
        ( g_Initializer.getThreadPool() ).run( boost::bind(&GroupInfoService::doCreateGroup,
                        this , conn , groupName , belong2Domain , description) );
    }
    else
    {
        GroupCreateACK reply;
        reply.set_statuscode(PERMISSION_DENIED);
        ( g_Initializer.getCodec() ).send(conn , reply);
    }
}

void GroupInfoService::onDeleteInfo(TcpConnectionPtr const& conn,
                                    MessagePtr const& msg,
                                    Timestamp time)
{
    GroupDestoryMsgPtr query = muduo::down_pointer_cast<GroupDestoryMsg>(msg);
    std::string tmp = query->token();
    Token token(tmp);
    if(token.niuXThanGroupAdmin())
    {
        std::string groupName = query->groupname();
        (g_Initializer.getThreadPool()).run(boost::bind(&GroupInfoService::doDeleteGroup,
            this , conn , groupName));
    }
    else
    {
        GroupDestoryACK reply;
        reply.set_statuscode(PERMISSION_DENIED);
        ( g_Initializer.getCodec() ).send(conn , reply);
    }
}

void GroupInfoService::onUpdateInfo(TcpConnectionPtr const& conn,
                                    MessagePtr const& msg,
                                    Timestamp time)
{
    GroupInfoUpdateMsgPtr query = muduo::down_pointer_cast<GroupInfoUpdateMsg>(msg);
    std::string tmp = query->token();
    Token token(tmp);
    if(token.niuXThanGroupAdmin())
    {
        std::string groupName = query->groupname();
        std::string description = query->groupdescription();
        (g_Initializer.getThreadPool()).run(boost::bind(&GroupInfoService::doUpdateGroup,
            this , conn , groupName , description));
    }
    else
    {
        GroupInfoUpdateACK reply;
        reply.set_statuscode(PERMISSION_DENIED);
        ( g_Initializer.getCodec() ).send(conn , reply);
    }
}

void GroupInfoService::onGetInfo(TcpConnectionPtr const& conn,
                                 MessagePtr const& msg,
                                 Timestamp time)
{
    GroupInfoGetMsgPtr query = muduo::down_pointer_cast<GroupInfoGetMsg>(msg);
    std::string tmp = query->token();
    Token token(tmp);
    if(token.niuXThanGroupAdmin())
    {
        std::string groupName = token.getGroup();
        (g_Initializer.getThreadPool()).run(boost::bind(&GroupInfoService::doGetGroup,
                                            this , conn , groupName));
    }
    else
    {
        GroupInfoGetACK reply;
        reply.set_statuscode(PERMISSION_DENIED);
        ( g_Initializer.getCodec() ).send(conn , reply);
    }
}

void GroupInfoService::doCreateGroup(TcpConnectionPtr const& conn , std::string groupName,
                   std::string domain , std::string description)
{
    ConnectionPtr dbConn = g_DbPool.getConnection<MysqlConnection>();
    ResultSetPtr result;
    GroupCreateACK reply;
    {
        MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
        MutexLockGuard guard(**lock);
        result = dbConn->executeQuery("select id from DOMAIN_INFO\
                                        where name = '%s' " , domain.c_str());
        if( result->next() )
        {
            result = dbConn->executeQuery("select id from GROUP_INFO where name = %s",
                                                groupName.c_str());
            if( !result->next() )
            {
                dbConn->execute("inert into GROUP_INFO(name , description , belong2Domain)\
                                        values('%s' , '%s' , '%s')" , groupName.c_str(),
                                        description.c_str() , domain.c_str());//lazy to write try-catch

                reply.set_statuscode(SUCCESS);
            }
            else
                reply.set_statuscode(EXISTED_GROUP);
        }
        else
            reply.set_statuscode(UNEXISTED_DOMAIN);
    }
    dbConn->close();
#ifndef TEST
    ( g_Initializer.getCodec() ).send(conn , reply);
#endif
}

void GroupInfoService::doDeleteGroup(TcpConnectionPtr const& conn , std::string groupName)
{
    ConnectionPtr dbConn = g_DbPool.getConnection<MysqlConnection>();
    GroupDestoryACK reply;
    ResultSetPtr result;
    try
    {
        {
            MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
            MutexLockGuard guard(**lock);
            result = dbConn->executeQuery("select id from GROUP_INFO\
                                        where name = '%s' " , groupName.c_str());
            if(result->next())
            {
                dbConn->execute("delete from GROUP_INFO where name = '%s' ",
                                groupName.c_str());
                reply.set_statuscode(SUCCESS);
            }
            else
                reply.set_statuscode(UNEXISTED_GROUP);
        }
    }
    catch(SQLException const& e)
    {
#ifdef DEBUG
        LOG_INFO << "failed to delete group: " << groupName;
#endif
        reply.set_statuscode(UNKNOWN_SYSERROR);

    }
    dbConn->close();
#ifndef TEST
    ( g_Initializer.getCodec() ).send(conn , reply);
#endif
}

void GroupInfoService::doUpdateGroup(TcpConnectionPtr const& conn , std::string groupName,
                   std::string description)
{
    ConnectionPtr dbConn = g_DbPool.getConnection<MysqlConnection>();
    GroupInfoUpdateACK reply;
    ResultSetPtr result;
    try
    {
        {
            MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
            MutexLockGuard guard(**lock);
            result = dbConn->executeQuery("select id from GROUP_INFO\
                                           where name = '%s' " , groupName.c_str());
            if(result->next())
            {
                dbConn->execute(" update GROUP_INFO set description = '%s' where name = '%s' ",
                    description.c_str() , groupName.c_str());

                reply.set_statuscode(SUCCESS);
            }
            else
                reply.set_statuscode(UNEXISTED_GROUP);
        }
    }
    catch(SQLException const& e)
    {
#ifdef DEBUG
        LOG_INFO << "failed to update group: " << groupName;
#endif
        reply.set_statuscode(UNKNOWN_SYSERROR);
    }
    dbConn->close();
#ifndef TEST
    ( g_Initializer.getCodec() ).send(conn , reply);
#endif
}

void GroupInfoService::doGetGroup(TcpConnectionPtr const& conn , std::string groupName)
{
    ConnectionPtr dbConn = g_DbPool.getConnection<MysqlConnection>();
    GroupInfoGetACK reply;
    ResultSetPtr result;
    try
    {
        {
            MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
            MutexLockGuard guard(**lock);
            result = dbConn->executeQuery("select id , description from GROUP_INFO\
                                            where name = '%s' " , groupName.c_str());
        }
        if(result->next())
        {
            std::string groupDescription = result->getString(2);
            reply.set_statuscode(SUCCESS);
            typedef MSG_DM_CLIENT_GROUP_DESCRIPTION_GET_ACK_GROUP_INFO GroupInfo;
            GroupInfo* info = reply.add_groupinfo();
            info->set_name(groupName);
            info->set_description(groupDescription);
        }
        else
            reply.set_statuscode(UNEXISTED_GROUP);
    }
    catch(SQLException const& e)
    {
#ifdef DEBUG
        LOG_INFO << "failed to get the info of group: " << groupName;
#endif
        reply.set_statuscode(UNKNOWN_SYSERROR);
    }
    dbConn->close();
#ifndef TEST
    ( g_Initializer.getCodec() ).send(conn , reply);
#endif
}