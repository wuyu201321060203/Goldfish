#include <DM/Token.h>
#include <Db/ConnectionPool.h>
#include <Db/ResultSet.h>
#include <mysql/MysqlConnection.h>

#include <zlib.h>

#include <boost/lexical_cast.hpp>

#include <stdexcept>

#include "gtest/gtest.h"

using namespace OOzdb;
using std::out_of_range;

extern ConnectionPool g_DbPool;

TEST(TokenTest , FirConstructTest)
{
    STDSTR username("ddcnmb");
    STDSTR belong2Domain("domain1");
    STDSTR belong2Group("group1");
    ConnectionPtr dbConn = g_DbPool.getConnection<MysqlConnection>();
    ResultSetPtr result = dbConn->executeQuery(
        "select identity from USER_INFO where name = 'ddcnmb'");
    unsigned int identity = 0b11111111;
    if(result->next())
        identity = result->getInt(1);
    Token token(username , identity , belong2Domain , belong2Group);
    STDSTR fakeToken("ddcnmb\r\n00000010\r\ndomain1\r\ngroup1\r\n");
    fakeToken += token.getCheckSumStr();
    EXPECT_EQ(fakeToken , token.toString());
    dbConn->close();
}

TEST(TokenTest , SecConstructTest)
{
    STDSTR username("ddcnmb");
    STDSTR belong2Domain("domain1");
    STDSTR belong2Group("group1");
    unsigned int identity = 0b00000010;
    Token token(username , identity , belong2Domain , belong2Group);
    STDSTR fake = token.toString();
    STDSTR result;
    EXPECT_NO_THROW({Token anotherToken(fake); result = anotherToken.toString();});
    EXPECT_EQ(fake , result);
    Token sample(result);
    EXPECT_EQ("ddcnmb" , sample.getUserName());
    EXPECT_EQ("00000010" , sample.getIdentity());
    EXPECT_EQ("domain1" , sample.getDomain());
    EXPECT_EQ("group1" , sample.getGroup());
    STDSTR fake2("a\r\nb\r\nc\r\nd\r\ne\r\nf\r\ng\r\n");
    EXPECT_THROW(
    {
        Token wrongToken(fake2);
    } , out_of_range
    );
}

TEST(TokenTest , niuXThanDATest)
{
    STDSTR username("ddcnmb");
    STDSTR belong2Domain("domain1");
    STDSTR belong2Group("group1");
    unsigned int identity = 0b00000000;
    Token token(username , identity , belong2Domain , belong2Group);
    EXPECT_TRUE(true == token.niuXThanDomainAdmin());
    identity = 0b00000010;
    Token token1(username , identity , belong2Domain , belong2Group);
    EXPECT_TRUE(false == token1.niuXThanDomainAdmin());
    identity = 0b00000100;
    Token token2(username , identity , belong2Domain , belong2Group);
    EXPECT_TRUE(false == token2.niuXThanDomainAdmin());
    identity = 0b00001000;
    Token token3(username , identity , belong2Domain , belong2Group);
    EXPECT_TRUE(false == token3.niuXThanDomainAdmin());
    identity = 0b00001001;
    Token token4(username , identity , belong2Domain , belong2Group);
    EXPECT_TRUE(false == token4.niuXThanDomainAdmin());
}

TEST(TokenTest , niuXThanGATest)
{
    STDSTR username("ddcnmb");
    STDSTR belong2Domain("domain1");
    STDSTR belong2Group("group1");
    unsigned int identity = 0b00000000;
    Token token(username , identity , belong2Domain , belong2Group);
    EXPECT_TRUE(true == token.niuXThanGroupAdmin());
    identity = 0b00000010;
    Token token1(username , identity , belong2Domain , belong2Group);
    EXPECT_TRUE(true == token1.niuXThanGroupAdmin());
    identity = 0b00000100;
    Token token2(username , identity , belong2Domain , belong2Group);
    EXPECT_TRUE(false == token2.niuXThanGroupAdmin());
    identity = 0b00001000;
    Token token3(username , identity , belong2Domain , belong2Group);
    EXPECT_TRUE(false == token3.niuXThanGroupAdmin());
    identity = 0b00001001;
    Token token4(username , identity , belong2Domain , belong2Group);
    EXPECT_TRUE(false == token4.niuXThanGroupAdmin());
}

TEST(TokenTest , niuXThanUserTest)
{
    STDSTR username("ddcnmb");
    STDSTR belong2Domain("domain1");
    STDSTR belong2Group("group1");
    unsigned int identity = 0b00000000;
    Token token(username , identity , belong2Domain , belong2Group);
    EXPECT_TRUE(true == token.niuXThanCommonUser());
    identity = 0b00000010;
    Token token1(username , identity , belong2Domain , belong2Group);
    EXPECT_TRUE(true == token1.niuXThanCommonUser());
    identity = 0b00000100;
    Token token2(username , identity , belong2Domain , belong2Group);
    EXPECT_TRUE(true == token2.niuXThanCommonUser());
    identity = 0b00001000;
    Token token3(username , identity , belong2Domain , belong2Group);
    EXPECT_TRUE(false == token3.niuXThanCommonUser());
    identity = 0b00001001;
    Token token4(username , identity , belong2Domain , belong2Group);
    EXPECT_TRUE(false == token4.niuXThanCommonUser());
}

TEST(TokenTest , equalTest)
{
    STDSTR username1("ddcnmb");
    STDSTR belong2Domain1("domain1");
    STDSTR belong2Group1("group1");
    unsigned int identity1 = 0b00000000;
    Token token1(username1 , identity1 , belong2Domain1 , belong2Group1);
    Token token2(username1 , identity1 , belong2Domain1 , belong2Group1);
    EXPECT_TRUE(true == (token1 == token2));
    unsigned int identity2 = 0b00000001;
    Token token3(username1 , identity2 , belong2Domain1 , belong2Group1);
    EXPECT_TRUE(false == (token1 == token3));
    STDSTR username2("ddsb");
    Token token4(username2 , identity1 , belong2Domain1 , belong2Group1);
    EXPECT_TRUE(false == (token1 == token4));
}