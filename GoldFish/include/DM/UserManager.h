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

    UserManager();

    void onUserLogin(muduo::net::TcpConnectionPtr const&,
                     MessagePtr const&,
                     muduo::Timestamp);

    void onVerifyEncryptedToken(muduo::net::TcpConnectionPtr const&,
                                MessagePtr const&,
                                muduo::Timestamp);

private:

    typedef std::vector<Token> TokenVec;
    TokenVec _rawTokenList;

    static void verifyIdentity(muduo::net::TcpConnectionPtr const&,
                               std::string,
                               std::string);
};

#endif