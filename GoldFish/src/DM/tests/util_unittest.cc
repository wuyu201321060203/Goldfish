#include <DM/util.h>
#include <string>
#include <muduo/base/Types.h>

#include "gtest/gtest.h"

TEST(UtilTest , Mu2StdTest)
{
    char s[] = "helloworld";
    muduo::string s1(s);
    std::string s2(MuduoStr2StdStr(s1));
    std::string s3(s);
    EXPECT_EQ(s3 , s2);
}

TEST(UtilTest , Std2MuTest)
{
    char s[] = "helloworld";
    std::string s1(s);
    muduo::string s2(StdStr2MuduoStr(s1));
    muduo::string s3(s);
    EXPECT_EQ(s3 , s2);
}