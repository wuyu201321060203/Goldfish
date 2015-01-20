#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <vector>

#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>

#include "CryptographicService.h"

class UserManager
{
public:

    UserManager(CryptographicService*);
    void onUserLogin(TcpConnectionPtr const&,
                     UserLoginMsgPtr const&,
                     muduo::Timestamp);

    void onVerifyEncryptedToken(TcpConnectionPtr const&,
                              TokenVerifyMsgPtr const&,
                              muduo::Timestamp);

    Token createEncryptedToken(string , string , int , int);

private:

    typedef std::vector<Token> TokenVec;
    TokenVec _rawTokenList;
    MutexLock _lock;
    CryptographicServicePtr _edServer;

private:

    inline Token createRawToken(string identity,
                                string belong2Group,
                                int import,
                                int lookup);

    inline int encryptRawToken(Token& rawToken);
    static void verifyIdentity(TcpConnectionPtr const& , string , string);
};

#endif