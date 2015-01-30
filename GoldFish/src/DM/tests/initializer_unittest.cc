#include <string.h>

#include <DM/Initializer.h>
#include <Db/ConnectionPool.h>
#include <Db/ResultSet.h>
#include <mysql/MysqlConnection.h>

#include "gtest/gtest.h"

Initializer g_Initializer;
OOzdb::ConnectionPool g_DbPool("mysql://root:123@localhost:3306/DM");

TEST(InitializerTest , InitTest)
{
    char* config[2] = {"test" , "-c /home/wuyu/Goldfish/GoldFish/src/DM/tests/test.lua"};
    EXPECT_EQ(0 , g_Initializer.init(2 , config) );
    EXPECT_EQ(45678 , g_Initializer.getOptions().getDCPort());
}

TEST(InitializerTest , registeMsgTest)
{
    uint32_t cmd1 = 1;
    uint32_t cmd2 = 2;
    std::string type1 = "hello";
    std::string type2 = "world";
    g_Initializer.registeRASMsg(cmd1 , type1);
    g_Initializer.registeRASMsg(cmd2 , type2);
    EXPECT_EQ(1 , g_Initializer.getCmdByTypename("hello"));
    EXPECT_EQ("world" , g_Initializer.getTypenameByCmd(2));
}