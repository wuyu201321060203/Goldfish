#include <DM/Token.h>
#include <Db/ConnectionPool.h>
#include <Db/ResultSet.h>
#include <mysql/MysqlConnection.h>

#include <zlib.h>

#include <boost/lexical_cast.hpp>

#include "gtest/gtest.h"

using namespace OOzdb;

extern ConnectionPool g_DbPool;

TEST(TokenTest , ConstructTest)
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