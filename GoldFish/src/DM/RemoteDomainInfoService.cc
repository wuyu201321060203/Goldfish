#include <string>

#ifdef TEST
#include <vector>
#include <iostream>
#endif

#include <boost/any.hpp>

#include <muduo/base/Logging.h>
#include <muduo/base/Types.h>
#include <muduo/base/Mutex.h>
#include <muduo/base/ThreadPool.h>

#include <DM/RemoteDomainInfoService.h>
#include <DM/Token.h>
#include <DM/ResourceManager.h>

#include <Db/ResultSet.h>
#include <Db/ConnectionPool.h>
#include <mysql/MysqlConnection.h>
#include <Exception/SQLException.h>

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;
using boost::any_cast;

typedef boost::shared_ptr<MutexLock> MutexLockPtr;

RemoteDomainInfoService::RemoteDomainInfoService(ResourceManagerPtr const& manager):
                            _manager(manager)
{
}

void RemoteDomainInfoService::onCreateInfo(TcpConnectionPtr const& conn,
                                           MessagePtr const& msg,
                                           muduo::Timestamp)
{
    DomainCreateMsgPtr query = muduo::down_pointer_cast<DomainCreateMsg>(msg);
    std::string tmp = query->token();
    Token token(tmp);
    if( token.niuXThanDomainAdmin() )
    {
        _manager->applyResource(query->domainname() , query->domaindescription(),
            query->corenum() , query->memsize() , conn);
    }
    else
        onTokenAuthFailed<DomainCreateACK>(conn);
}

void RemoteDomainInfoService::onDeleteInfo(TcpConnectionPtr const& conn,
                                           MessagePtr const& msg,
                                           muduo::Timestamp)
{
    DomainDestroyMsgPtr query = muduo::down_pointer_cast<DomainDestroyMsg>(msg);
    std::string tmp = query->token();
    Token token(tmp);
    if( token.niuXThanDomainAdmin() )
    {
        uint32_t id = query->domainid();
        _manager->revokeResource(id);
    }
    else
        onTokenAuthFailed<DomainDestroyACK>(conn);
}

void RemoteDomainInfoService::onUpdateInfo(TcpConnectionPtr const& conn,
                                           MessagePtr const& msg,
                                           muduo::Timestamp)
{
    DomainInfoUpdateMsgPtr query = muduo::down_pointer_cast<DomainInfoUpdateMsg>(msg);
    std::string tmp = query->token();
    Token token(tmp);
    if(token.niuXThanGroupAdmin())
    {
        std::string domainName = query->domainname();
        std::string description = query->domaindescription();
        (Initializer::getThreadPool()).run(boost::bind(&DomainInfoService::doUpdateDomain,
            this , conn , domainName , description));
    }
    else
        onTokenAuthFailed<DomainInfoUpdateACK>(conn);
}

void RemoteDomainInfoService::onGetInfo(TcpConnectionPtr const& conn,
                                        MessagePtr const& msg,
                                        muduo::Timestamp)
{
    DomainInfoGetMsgPtr query = muduo::down_pointer_cast<DomainInfoGetMsg>(msg);
    std::string tmp = query->token();
    Token token(tmp);
    std::string domainName = token.getDomain();
    (Initializer::getThreadPool()).run(boost::bind(&DomainInfoService::doGetDomain,
                                        this , conn , domainName));
}

void RemoteDomainInfoService::doUpdateDomain(TcpConnectionPtr const& conn,
                                             std::string domainName,
                                             std::string description)
{
    ConnectionPtr dbConn = Initializer::getDbPool().getConnection<MysqlConnection>();
    DomainInfoUpdateACK reply;
    ResultSetPtr result;
    try
    {
        {
            MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
            MutexLockGuard guard(**lock);
            result = dbConn->executeQuery("select id from DOMAIN_INFO\
                                           where name = '%s' " , domainName.c_str());
            if(result->next())
            {
                dbConn->execute(" update DOMAIN_INFO set description = '%s' where name = '%s' ",
                    description.c_str() , domainName.c_str());

                reply.set_statuscode(SUCCESS);
            }
            else
                reply.set_statuscode(UNEXISTED_DOMAIN);
        }
    }
    catch(SQLException const& e)
    {
#ifdef DEBUG
        LOG_INFO << "failed to update domain: " << domainName;
#endif
        reply.set_statuscode(UNKNOWN_SYSERROR);
    }
    dbConn->close();
#ifndef TEST
    ( Initializer::getCodec() ).send(conn , reply);
#endif
}

void RemoteDomainInfoService::doGetDomain(TcpConnectionPtr const& conn , std::string domainName)
{
    typedef MSG_DM_CLIENT_DOMAIN_DESCRIPTION_GET_ACK_DOMAIN_INFO DomainInfo;
    ConnectionPtr dbConn = (Initializer::getDbPool()).getConnection<MysqlConnection>();
    DomainInfoGetACK reply;
    reply.set_statuscode(UNEXISTED_DOMAIN);
    ResultSetPtr result;
    std::string sqlQuery;
    std::string domainDescription;
    std::string domainNameAlias;
    if(domainName != "*")
    {
        std::string prefix("select name , description from DOMAIN_INFO where name = '");
        sqlQuery = prefix + domainName + "'";
    }
    else
        sqlQuery = "select name , description from DOMAIN_INFO";
    try
    {
        {
            MutexLockPtr* lock = any_cast<MutexLockPtr>(conn->getMutableContext());
            MutexLockGuard guard(**lock);
            result = dbConn->executeQuery(sqlQuery.c_str());
        }
        while(result->next())
        {
            domainNameAlias = result->getString(1);
            domainDescription = result->getString(2);
            reply.set_statuscode(SUCCESS);
            DomainInfo* info = reply.add_domaininfo();
            info->set_name(domainNameAlias);
            info->set_description(domainDescription);
        }
    }
    catch(SQLException const& e)
    {
#ifdef DEBUG
        LOG_INFO << "failed to get the info of domain: " << domainName;
#endif
        reply.set_statuscode(UNKNOWN_SYSERROR);
    }
    dbConn->close();
#ifndef TEST
    ( Initializer::getCodec() ).send(conn , reply);
#endif
}