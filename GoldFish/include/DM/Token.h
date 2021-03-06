#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <bitset>

typedef unsigned long ulong;
typedef std::string STDSTR;

static ulong const ROOT_AUTH = 0b00000000;
static ulong const DOMAINADMIN_AUTH = 0b00000010;
static ulong const GROUPADMIN_AUTH = 0b00000100;
static ulong const USER_IMPORT_AUTH = 0b00001000;
static ulong const USER_QUERY_AUTH = 0b00001001;
static ulong const USER_IMPORT_QUERY_AHTH = 0b00001010;

#define IDENTITY_WIDTH 8

class Token
{
public:

    Token(STDSTR , unsigned long , STDSTR , STDSTR);
    Token(STDSTR);
    STDSTR toString();
    STDSTR getUserName() const;
    STDSTR getIdentity() const;
    STDSTR getDomain() const;
    STDSTR getGroup() const;
    STDSTR getCheckSumStr() const;
    bool niuXThanDomainAdmin();
    bool niuXThanGroupAdmin();
    bool niuXThanCommonUser();
    bool canImportOrNot();
    bool canQueryOrNot();
    bool operator==(Token const&);

private:

    STDSTR _username;
    std::bitset<IDENTITY_WIDTH> _identity;
    STDSTR _belong2Domain;
    STDSTR _belong2Group;
    STDSTR const _delimiter;
    STDSTR _checkSum;
    STDSTR _token;

private:

    int addCheckSum();
};

#endif