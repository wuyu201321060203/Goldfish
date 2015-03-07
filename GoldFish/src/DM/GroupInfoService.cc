#include <string>

#ifdef TEST
#include <vector>
#include <iostream>
#endif

#include <boost/bind.hpp>
#include <boost/any.hpp>

#ifdef DMDEBUG
#include <muduo/base/Logging.h>
#endif
#include <muduo/base/Types.h>
//#include <muduo/base/Mutex.h>
#include <muduo/base/ThreadPool.h>

#include <DM/GroupInfoService.h>
#include <DM/Token.h>

#include <Db/ResultSet.h>
#include <Db/ConnectionPool.h>
#include <mysql/MysqlConnection.h>
#include <Exception/SQLException.h>

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;
using boost::any_cast;

//typedef boost::shared_ptr<MutexLock> MutexLockPtr;

#ifdef TEST
typedef MSG_DM_CLIENT_GROUP_DESCRIPTION_GET_ACK_GROUP_INFO GroupInfoType;
extern std::vector<GroupInfoType> testArray;
#endif

GroupInfoService::GroupInfoService()
{
    ( Initializer::getDispatcher() ).registerMessageCallback(
        GroupCreateMsg::descriptor(),
        boost::bind(&GroupInfoService::onCreateInfo , this , _1 , _2 , _3)
        );

    ( Initializer::getDispatcher() ).registerMessageCallback(
        GroupDestroyMsg::descriptor(),
        boost::bind(&GroupInfoService::onDeleteInfo , this , _1 , _2 , _3)
        );

    ( Initializer::getDispatcher() ).registerMessageCallback(
        GroupInfoUpdateMsg::descriptor(),
        boost::bind(&GroupInfoService::onUpdateInfo , this , _1 , _2 , _3)
        );

    ( Initializer::getDispatcher() ).registerMessageCallback(
        GroupInfoGetMsg::descriptor(),
        boost::bind(&GroupInfoService::onGetInfo , this , _1 , _2 , _3)
        );
}

void GroupInfoService::onCreateInfo(TcpConnectionPtr const& conn,
                                    MessagePtr const& msg,
                                    Timestamp time)
{
    GroupCreateMsgPtr query = muduo::down_pointer_cast<GroupCreateMsg>(msg);
    std::string tmp = query->token();
    ( Initializer::getDesEcbAcceptor() )->decode(tmp);
    Token token(tmp);
    if(token.niuXThanGroupAdmin())
    {
        std::string groupName = query->groupname();
        std::string belong2Domain = query->belong2domain();
        std::string description = query->groupdescription();
        ( Initializer::getThreadPool() ).run( boost::bind(&GroupInfoService::doCreateGroup,
                        this , conn , groupName , belong2Domain , description) );
    }
    else
        onTokenAuthFailed<GroupCreateACK>(conn);
}

void GroupInfoService::onDeleteInfo(TcpConnectionPtr const& conn,
                                    MessagePtr const& msg,
                                    Timestamp time)
{
    GroupDestroyMsgPtr query = muduo::down_pointer_cast<GroupDestroyMsg>(msg);
    std::string tmp = query->token();
    ( Initializer::getDesEcbAcceptor() )->decode(tmp);
    Token token(tmp);
    if(token.niuXThanGroupAdmin())
    {
        std::string groupName = query->groupname();
        (Initializer::getThreadPool()).run(boost::bind(&GroupInfoService::doDeleteGroup,
            this , conn , groupName));
    }
    else
        onTokenAuthFailed<GroupDestroyACK>(conn);
}

void GroupInfoService::onUpdateInfo(TcpConnectionPtr const& conn,
                                    MessagePtr const& msg,
                                    Timestamp time)
{
    GroupInfoUpdateMsgPtr query = muduo::down_pointer_cast<GroupInfoUpdateMsg>(msg);
    std::string tmp = query->token();
    ( Initializer::getDesEcbAcceptor() )->decode(tmp);
    Token token(tmp);
    if(token.niuXThanGroupAdmin())
    {
        std::string groupName = query->groupname();
        std::string description = query->groupdescription();
        (Initializer::getThreadPool()).run(boost::bind(&GroupInfoService::doUpdateGroup,
            this , conn , groupName , description));
    }
    else
        onTokenAuthFailed<GroupInfoUpdateACK>(conn);
}

void GroupInfoService::onGetInfo(TcpConnectionPtr const& conn,
                                 MessagePtr const& msg,
                                 Timestamp time)
{
    GroupInfoGetMsgPtr query = muduo::down_pointer_cast<GroupInfoGetMsg>(msg);
    std::string tmp = query->token();
    ( Initializer::getDesEcbAcceptor() )->decode(tmp);
    Token token(tmp);
    std::string groupName = token.getGroup();
    (Initializer::getThreadPool()).run(boost::bind(&GroupInfoService::doGetGroup,
        this , conn , groupName));
}

void GroupInfoService::doCreateGroup(TcpConnectionPtr const& conn , std::string groupName,
                                     std::string domain , std::string description)
{
    ConnectionPtr dbConn = (Initializer::getDbPool()).getConnection<MysqlConnection>();
    //ResultSetPtr result;
    GroupCreateACK reply;
    try
    {
        //{
        //MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
        //MutexLockGuard guard(**lock);
        ResultSetPtr result = dbConn->executeQuery("select id from DOMAIN_INFO\
            where name = '%s' " , domain.c_str());
        if( result->next() )
        {
            int domainID = result->getInt(1);
            result = dbConn->executeQuery("select id from GROUP_INFO where name = '%s' ",
                groupName.c_str());
            if( !result->next() )
            {
                dbConn->execute("insert into GROUP_INFO(name , description , belong2Domain)\
                    values('%s' , '%s' , '%d')" , groupName.c_str(),
                    description.c_str() , domainID);

                reply.set_statuscode(SUCCESS);
            }
            else
                reply.set_statuscode(EXISTED_GROUP);
        }
        else
            reply.set_statuscode(UNEXISTED_DOMAIN);
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

void GroupInfoService::doDeleteGroup(TcpConnectionPtr const& conn , std::string groupName)
{
    ConnectionPtr dbConn = (Initializer::getDbPool()).getConnection<MysqlConnection>();
    GroupDestroyACK reply;
    //ResultSetPtr result;
    try
    {
        //{
        //MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
        //MutexLockGuard guard(**lock);
        ResultSetPtr result = dbConn->executeQuery("select id from GROUP_INFO\
            where name = '%s' " , groupName.c_str());
        if(result->next())
        {
            dbConn->execute("delete from GROUP_INFO where name = '%s' ",
                groupName.c_str());
            reply.set_statuscode(SUCCESS);
        }
        else
            reply.set_statuscode(UNEXISTED_GROUP);
        //}
    }
    catch(SQLException const& e)
    {
#ifdef DMDEBUG
        LOG_INFO << "failed to delete group: " << groupName;
#endif
        reply.set_statuscode(UNKNOWN_SYSERROR);

    }
    dbConn->close();
#ifndef TEST
    ( Initializer::getCodec() ).send(conn , reply);
#endif
}

void GroupInfoService::doUpdateGroup(TcpConnectionPtr const& conn , std::string groupName,
                   std::string description)
{
    ConnectionPtr dbConn = Initializer::getDbPool().getConnection<MysqlConnection>();
    GroupInfoUpdateACK reply;
    //ResultSetPtr result;
    try
    {
        //{
        //MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
        //MutexLockGuard guard(**lock);
        ResultSetPtr result = dbConn->executeQuery("select id from GROUP_INFO\
            where name = '%s' " , groupName.c_str());
        if(result->next())
        {
            dbConn->execute(" update GROUP_INFO set description = '%s' where name = '%s' ",
                description.c_str() , groupName.c_str());

            reply.set_statuscode(SUCCESS);
        }
        else
            reply.set_statuscode(UNEXISTED_GROUP);
        //}
    }
    catch(SQLException const& e)
    {
#ifdef DMDEBUG
        LOG_INFO << "failed to update group: " << groupName;
#endif
        reply.set_statuscode(UNKNOWN_SYSERROR);
    }
    dbConn->close();
#ifndef TEST
    ( Initializer::getCodec() ).send(conn , reply);
#endif
}

void GroupInfoService::doGetGroup(TcpConnectionPtr const& conn , std::string groupName)
{
    typedef MSG_DM_CLIENT_GROUP_DESCRIPTION_GET_ACK_GROUP_INFO GroupInfo;
    ConnectionPtr dbConn = (Initializer::getDbPool()).getConnection<MysqlConnection>();
    GroupInfoGetACK reply;
    reply.set_statuscode(UNEXISTED_GROUP);
    //ResultSetPtr result;
    std::string sqlQuery;
    std::string groupDescription;
    std::string groupNameAlias;
    if(groupName != "*")
    {
        std::string prefix("select name , description from GROUP_INFO where name = '");
        sqlQuery = prefix + groupName + "'";
    }
    else
        sqlQuery = "select name , description from GROUP_INFO";
    try
    {
        //{
        //MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
        //MutexLockGuard guard(**lock);
        ResultSetPtr result = dbConn->executeQuery(sqlQuery.c_str());
        //}
        while(result->next())
        {
            groupNameAlias = result->getString(1);
            groupDescription = result->getString(2);
            reply.set_statuscode(SUCCESS);
            GroupInfo* info = reply.add_groupinfo();
            info->set_name(groupNameAlias);
            info->set_description(groupDescription);
#ifdef TEST
            testArray.push_back(*info);
#endif

        }
    }
    catch(SQLException const& e)
    {
#ifdef DMDEBUG
        LOG_INFO << "failed to get the info of group: " << groupName;
#endif
        reply.set_statuscode(UNKNOWN_SYSERROR);
    }
    dbConn->close();
#ifndef TEST
    ( Initializer::getCodec() ).send(conn , reply);
#endif
}