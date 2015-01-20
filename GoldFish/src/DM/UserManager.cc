#include <boost/bind.hpp>

#include "UserManager.h"

extern Initializer g_Initializer;

UserManager::UserManager(CryptographicService* server):_edServer(server)
{
}

void UserManager::onUserLogin(TcpConnectionPtr const& conn,
                              MessagePtr const& msg,
                              muduo::Timestamp)
{
    boost::shared_ptr<UserLoginMsg> query = muduo::down_cast<UserLoginMsg>(msg);
    string username = query->userName();
    string passwd = query->password();
    (g_Initializer.getThreadPool()).run(boost::bind(&verifyIdentity , conn ,
                                        username , passwd));
}

void UserManager::verifyEncryptedToken(TcpConnectionPtr const& conn,
                          MessagePtr const& msg,
                          muduo::Timestamp)
{
    boost::shared_ptr<TokenVerifyMsg> query = muduo::down_cast<TokenVerifyMsg>(msg);
    Token token = query->token();
    _edServer->decode(token);
    TokenVec::iterator iter = _rawTokenList.find(token);
    TokenVerifyACKMsg replyMsg;
    if(iter != _rawTokenList.end())
        replyMsg.set_statusCode(SUCCESS);
    else
        replyMsg.set_statusCode(TOKEN_AUTH_FAIL);
    conn->send(replyMsg);
}

Token UserManager::createEncryptedToken(string identity , string belong2Group,
                                        int import , int lookup)
{
    Token rawToken = createRawToken(identity , belong2Group , import , lookup);
    if(encryptRawToken(token))
        return token;
    else
        LOG_INFO << "create encrypted token failed";

}

Token UserManager::createRawToken(string identity,
                            string belong2Group,
                            int import,
                            int lookup)
{
    Token token(identity + "\r\n" + belong2Group + "\r\n" + import +"\r\n" +
        lookup + "\r\n");

    int32_t checkSum = static_cast<int32_t>(
        ::adler32(1,
        reinterpret_cast<const Bytef*>(token.c_str()),
        static_cast<int>(toke.size())));
    string checkSumStr = boost::lexical_cast<string>(checkSum);
    token += checkSum;
    return token;
}

int UserManager::encryptRawToken(Token& token)
{
    if(_edServer->encrypt(token))
        return SUCCESS;
    else
        return FAIL;
}

void UserManager::verifyIdentity(TcpConnectionPtr const& conn , string name,
                                 string passwd)
{
    ConnectionPtr dbConn = SingleConnectionPool::instance().
                           getConnection<MysqlConnection>();
    ResultPtr result = dbConn->executeQuery(
        "select domain from User where name = %s and passwd = %s" , name , passwd);

    UserLoginACK replyMsg;
    if(result)
    {
       replyMsg.set_statusCode(SUCCESS);
       if(result->next())
           string domain = result->getString(1);
       result = dbConn->executeQuery(
                        "select ip , port from Domain where name = %s" , domain);
       if(result->next())
       {
           string ip = result->getString(1);
           string port = result->getString(2);
           replyMsg.set_DCIp(ip);
           replyMsg.set_DCPort(port);
           Token token = _edServer.createEncryptedToken();
           replyMsg.set_token(token);
       }
    }
    else
       replyMsg.set_statusCode(USER_NOT_EXIST);
    dbConn->close();
    conn->send(replyMsg);
}