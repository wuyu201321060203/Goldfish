#include <DM/Token.h>
#include <DM/Config.h>

#include <muduo/base/Logging.h>

#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>

#include <vector>
#include <stdexcept>

#include <zlib.h>

using namespace muduo;
using std::vector;
using std::out_of_range;

Token::Token(STDSTR username , ulong identity , STDSTR belong2Domain,
             STDSTR belong2Group):
             _username(username) , _identity(identity) , _belong2Domain(belong2Domain),
             _belong2Group(belong2Group) , _delimiter("\r\n")
{
    _token = _username + _delimiter + (_identity.to_string()) + _delimiter +
             _belong2Domain + _delimiter + _belong2Group + _delimiter;
    int ret = addCheckSum();
    if(ret != RET_SUCCESS)
    {
#ifdef DMDEBUG
        LOG_INFO << "Failed to add checksum for token";
#endif
    }
}

Token::Token(STDSTR token):_token(token)
{
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep("\r\n");
    tokenizer tokens(_token, sep);
    vector<STDSTR> temp;
    temp.reserve(TOKEN_ITEM_NUM + 1);
    for(tokenizer::iterator tok_iter = tokens.begin() ; tok_iter != tokens.end();
        ++tok_iter)
    {
        temp.push_back(*tok_iter);
    }
    if(temp.size() == TOKEN_ITEM_NUM + 1)
        temp.pop_back();
    if( ( temp.size() > TOKEN_ITEM_NUM) ) throw out_of_range("unknown token style");
    int pos = 0;
    try
    {
        _username = temp.at(pos++);
        std::bitset<IDENTITY_WIDTH> muddy( temp.at(pos++) );
        _identity = muddy;
        _belong2Domain = temp.at(pos++);
        _belong2Group = temp.at(pos++);
        _checkSum = temp.at(pos++);
    }
    catch(std::out_of_range const& e)
    {
        LOG_INFO << "unknown token: " << _token;
    }
}

STDSTR Token::toString()
{
    return _token;
}

STDSTR Token::getUserName() const
{
    return _username;
}

STDSTR Token::getIdentity() const
{
    return ( _identity.to_string() );
}

STDSTR Token::getDomain() const
{
    return _belong2Domain;
}

STDSTR Token::getGroup() const
{
    return _belong2Group;
}

STDSTR Token::getCheckSumStr() const
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

bool Token::canImportOrNot()
{
    if( _identity.to_ulong() != USER_QUERY_AUTH )
        return true;
    else
        return false;
}

bool Token::canQueryOrNot()
{
    if( _identity.to_ulong() != USER_IMPORT_AUTH )
        return true;
    else
        return false;
}

bool Token::operator==(Token const& rhs)
{
    return ( (_username == rhs.getUserName()) && (_identity.to_string() == rhs.getIdentity()) &&
            (_belong2Domain == rhs.getDomain()) && (_belong2Group == rhs.getGroup()) );
}

int Token::addCheckSum()
{
    int32_t checkSum = static_cast<int32_t>(
        ::adler32(1,
        reinterpret_cast<const Bytef*>(_token.c_str()),
        static_cast<int>(_token.size())));
    STDSTR checkSumStr = boost::lexical_cast<STDSTR>(checkSum);
    _checkSum = checkSumStr;
    _token += (checkSumStr + _delimiter);
    return RET_SUCCESS;
}