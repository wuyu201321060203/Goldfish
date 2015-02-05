#include <string.h>

#include <DM/Initializer.h>
#include <Db/ConnectionPool.h>
#include <Db/ResultSet.h>
#include <mysql/MysqlConnection.h>

#include "gtest/gtest.h"

OOzdb::ConnectionPool g_DbPool("mysql://root:123@localhost:3306/DM");

TEST(InitializerTest , InitTest)
{
    char* config[9] = {"test" , "1" , "2" , "ha" , "lo" , "3" , "4" , "0.0" , "5"};
    EXPECT_EQ(0 , Initializer::init(9 , config) );
    EXPECT_EQ(1 , Initializer::getFrameworkID());
    EXPECT_EQ(2 , Initializer::getFrameworkInstanceID());
    EXPECT_EQ("ha" , Initializer::getDockerTag());
    EXPECT_EQ("lo" , Initializer::getExecFilePathList());
    EXPECT_EQ(3 , Initializer::getCliPort());
    EXPECT_EQ(4 , Initializer::getDCPort());
    EXPECT_EQ("0.0" , Initializer::getRCIP());
    EXPECT_EQ(5 , Initializer::getRCPort());
}

TEST(InitializerTest , registeMsgTest)
{
    uint32_t cmd1 = 1;
    uint32_t cmd2 = 2;
    std::string type1 = "hello";
    std::string type2 = "world";
    Initializer::registeRASMsg(cmd1 , type1);
    Initializer::registeRASMsg(cmd2 , type2);
    EXPECT_EQ(1 , Initializer::getCmdByTypename("hello"));
    EXPECT_EQ("world" , Initializer::getTypenameByCmd(2));
}