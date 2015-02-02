#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <vector>
#include <string>

#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>

#include "Token.h"
#include "Config.h"

class UserManager
{
public:

    void onUserLogin(muduo::net::TcpConnectionPtr const&,
                     MessagePtr const&,
                     muduo::Timestamp);

    void onVerifyEncryptedToken(muduo::net::TcpConnectionPtr const&,
                                MessagePtr const&,
                                muduo::Timestamp);

private:

    typedef std::vector<Token> TokenVec;
    TokenVec _rawTokenList;

private:

    Token createEncryptedToken(std::string , unsigned long , std::string,
                               std::string);

    inline int encryptRawToken(Token& rawToken);
    static void verifyIdentity(muduo::net::TcpConnectionPtr const&,
                               std::string,
                               std::string);
};

#endif