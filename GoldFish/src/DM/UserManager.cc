#include <muduo/base/Logging.h>

#include <Exception/Exception.h>
#include <Exception/SQLException.h>
#include <Db/ConnectionPool.h>
#include <mysql/MysqlConnection.h>

#include <DM/UserManager.h>
#include <DM/Config.h>
#include <DM/Initializer.h>
#include <DM/Token.h>

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;

#ifdef TEST
extern UserLoginACK testLogin;
#endif

UserManager::UserManager()
{
    ( Initializer::getDispatcher() ).registerMessageCallback(
        UserLoginMsg::descriptor(),
        boost::bind(&UserManager::onUserLogin , this , _1 , _2 , _3)
        );
}

void UserManager::onUserLogin(TcpConnectionPtr const& conn,
                              MessagePtr const& msg,
                              muduo::Timestamp)
{
    UserLoginMsgPtr query = muduo::down_pointer_cast<UserLoginMsg>(msg);
    STDSTR username = query->username();
    STDSTR passwd = query->password();
    (Initializer::getThreadPool()).run(boost::bind(&verifyIdentity , conn,
                                        username , passwd));
}

void UserManager::verifyIdentity(TcpConnectionPtr const& conn , STDSTR name,
                                 STDSTR passwd)
{
    ConnectionPtr dbConn = ( Initializer::getDbPool() ).getConnection<MysqlConnection>();
    UserLoginACK reply;
    try
    {
        ResultSetPtr result = dbConn->executeQuery("select name, identity, belong2Domain, \
            belong2Group from USER_INFO where name = '%s' and passwd = '%s'" ,
            name.c_str() , passwd.c_str());
        if(result->next())
        {
            STDSTR username = result->getString(1);
            ulong authority = result->getInt(2);
            int belong2Domain = result->getInt(3);
            int belong2Group = result->getInt(4);
            STDSTR domainName;
            STDSTR groupName;
            result = dbConn->executeQuery("select name from GROUP_INFO where id = '%d'",
                                            belong2Group);
            if(result->next())
            {
                groupName = result->getString(1);
                result = dbConn->executeQuery("select name, IP, Port from DOMAIN_INFO \
                    where id = '%d'" , belong2Domain);
                if(result->next())
                {
                    domainName = result->getString(1);
                    STDSTR ip = result->getString(2);
                    int port = result->getInt(3);
#ifndef TEST
                    Token rawToken(username , authority , domainName , groupName);
                    STDSTR tokenStr(rawToken.toString());

                    ( Initializer::getDesEcbAcceptor() ).encrypt(tokenStr);
#else
                    STDSTR tokenStr("helloworld");
#endif
                    reply.set_token(tokenStr);
                    reply.set_dcip(ip);
                    reply.set_dcport(port);
                    reply.set_statuscode(SUCCESS);
                }
                else
                    THROW(SQLException , "Unexisted domain");
            }
            else
                THROW(SQLException , "Unexisted group");
        }
        else
            reply.set_statuscode(UNEXISTED_USER);
    }
    catch(SQLException const& e)
    {
#ifdef DEBUG
        LOG_INFO << "query error in user login" << groupName;
#endif
        reply.set_statuscode(UNKNOWN_SYSERROR);
    }
#ifdef TEST
    testLogin = reply;
#endif
   dbConn->close();
#ifndef TEST
    ( Initializer::getCodec() ).send(conn , reply);
#endif
}