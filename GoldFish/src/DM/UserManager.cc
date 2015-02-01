#include <muduo/base/Logging.h>

#include <Exception/Exception.h>
#include <Exception/SQLException.h>
#include <Db/ConnectionPool.h>
#include <mysql/MysqlConnection.h>

#include <DM/UserManager.h>
#include <DM/Config.h>
#include <Dm/Initializer.h>


extern Initializer g_Initializer;

using namespace muduo;
using namespace muduo::net;
using namespace OOzdb;

void UserManager::onUserLogin(TcpConnectionPtr const& conn,
                              MessagePtr const& msg,
                              muduo::Timestamp)
{
    UserLoginMsgPtr query = muduo::down_pointer_cast<UserLoginMsg>(msg);
    STDSTR username = query->username();
    STDSTR passwd = query->password();
    (g_Initializer.getThreadPool()).run(boost::bind(&verifyIdentity , conn,
                                        username , passwd));
}

void UserManager::onVerifyEncryptedToken(TcpConnectionPtr const& conn,
                                         MessagePtr const& msg,
                                         muduo::Timestamp)
{
    TokenIdentifyMsgPtr query = muduo::down_pointer_cast<TokenIdentifyMsg>(msg);
    STDSTR tmp = query->encryptedtoken();
    Token encryptedToken(tmp);
    //decode
    TokenVec::iterator iter = _rawTokenList.find(rawToken);//TODO
    TokenIdentifyACK reply;
    if(iter != _rawTokenList.end())
        reply.set_statuscode(SUCCESS);
    else
        reply.set_statuscode(TOKEN_AUTH_FAIL);
#ifdef TEST
    (g_Initializer.getCodec()).send(conn , reply);
#endif
}

STDSTR UserManager::createEncryptedToken(STDSTR username , ulong identity,
                                        STDSTR belong2Domain , STDSTR belong2Group)
{
    Token rawToken(username , identity , belong2Domain , belong2Group);
    STDSTR encryptedTokenStr;
    if( encryptRawToken( token.toString() , encryptedTokenStr ) )//TODO
        return encryptedTokenStr;
    else
        LOG_INFO << "create encrypted token failed";
}

void UserManager::verifyIdentity(TcpConnectionPtr const& conn , STDSTR name,
                                 STDSTR passwd)
{
    ConnectionPtr dbConn = g_DbPool.getConnection<MysqlConnection>();
    UserLoginACK reply;
    try
    {
        ResultSetPtr result = dbConn->executeQuery("select name , identity , belong2Domain , \
            belong2Group from USER_INFO where name = '%s' and passwd = '%s'",
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
                    STDSTR tokenStr = createEncryptedToken(username , authority,
                        domainName , groupName);
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
    dbConn->close();
#ifndef TEST
    ( g_Initializer.getCodec() ).send(conn , reply);
#endif
}