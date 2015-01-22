#include <DM/Token.h>
#include <DM/Config.h>

#include <muduo/base/Logging.h>

#include <boost/lexical_cast.hpp>

#include <zlib.h>

using namespace muduo;

Token::Token(STDSTR username , ulong identity , STDSTR belong2Domain,
             STDSTR belong2Group):
             _username(username) , _identity(identity) , _belong2Domain(belong2Domain),
             _belong2Group(belong2Group) , _delimiter("\r\n")
{
    _token = _username + _delimiter + (_identity.to_string()) + _delimiter +
             _belong2Domain + _delimiter + _belong2Group + _delimiter;
    int ret = addCheckSum();
    if(ret != RET_SUCCESS) LOG_INFO << "Failed to add checksum for token";
}

Token::Token(STDSTR token):_token(token)
{
}

STDSTR Token::toString()
{
    return _token;
}

int Token::addCheckSum()
{
    int32_t checkSum = static_cast<int32_t>(
        ::adler32(1,
        reinterpret_cast<const Bytef*>(_token.c_str()),
        static_cast<int>(_token.size())));
    STDSTR checkSumStr = boost::lexical_cast<STDSTR>(checkSum);
    _checkSum = checkSumStr;
    _token += checkSumStr;
    return RET_SUCCESS;
}

STDSTR Token::getCheckSumStr()
{
    return _checkSum;
}

bool Token::niuXThanDomainAdmin()
{
    return !( (_identity.to_ulong()) | ROOT_AUTH );
}

bool Token::niuXThanGroupAdmin()
{
   return !( ( _identity.to_ulong() ) & (USER_IMPORT_AUTH | GROUPADMIN_AUTH) );
}

bool Token::niuXThanCommonUser()
{
    return !( ( _identity.to_ulong() ) & (USER_IMPORT_AUTH) );
}