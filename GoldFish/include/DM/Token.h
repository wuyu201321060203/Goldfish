#ifndef TOKEN_H
#define TOKEN_H

#include <bitset>

static long const ROOT_AUTH = 0x00000000;
static long const DOMAINADMIN_AUTH = 0x00000010;
static long const GROUPADMIN_AUTH = 0x00000011;
static long const USER_IMPORT_AUTH = 0x00000100;
static long const USER_QUERY_AUTH = 0x00000101;

class Token
{
public:

    Token(int identity , string belong2Group , string import , string lookup):
            _identity(identity) , _belong2Group(belong2Group) , _import(import),
            _lookup(lookup) , _delimiter("\r\n")
    {
        _token = identity.to_string() + _delimiter + belong2Group + _delimiter +
                import + _delimiter + lookup + _delimiter;

        int ret = addCheckSum();
        if(ret != SUCCESS)
            LOG_INFO << ;//TODO
    }

    Token(string token):_token(token)
    {
    }

    string toString()
    {
        return _token;
    }

    int addCheckSum()
    {
        int32_t checkSum = static_cast<int32_t>(
            ::adler32(1,
            reinterpret_cast<const Bytef*>(_token.c_str()),
            static_cast<int>(toke.size())));
        string checkSumStr = boost::lexical_cast<string>(checkSum);
        _token += checkSum;
        return SUCCESS;
    }

    bool niuXThanDomainAdmin()
    {
        return _identity > DOMAINADMIN_AUTH;
    }

    bool niuXThanGroupAdmin()
    {
       return _identity >GROUPADMIN_AUTH;
    }

    bool niuXThanCommonUser()
    {
        return _identity > USER_AUTH;
    }

private:

    std::bitset<4> _identity;
    string _belong2Group;
    string _import;
    string _lookup;
    string const _delimiter;

private:

    string _token;
};

#endif