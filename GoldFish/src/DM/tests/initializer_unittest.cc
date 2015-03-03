#include <string.h>

#include <DM/Initializer.h>
#include <Db/ConnectionPool.h>
#include <Db/ResultSet.h>
#include <mysql/MysqlConnection.h>

#include "gtest/gtest.h"

OOzdb::ConnectionPool g_DbPool("mysql://root:123@localhost:3306/DM");

TEST(InitializerTest , InitTest)
{
    char* config[9] = {"test" , "1" , "2" , "3" ,  "9878" , "9879" , "127.0.0.1" , "9877" , "127.0.0.1"};
    EXPECT_EQ(0 , Initializer::init(9 , config) );
    EXPECT_EQ(1 , Initializer::getFrameworkID());
    EXPECT_EQ(2 , Initializer::getFrameworkInstanceID());
    EXPECT_EQ(3 , Initializer::getSelfModuleID());
    EXPECT_EQ(9878 , Initializer::getCliPort());
    EXPECT_EQ(9879 , Initializer::getDCPort());
    EXPECT_EQ("127.0.0.1" , Initializer::getRCIP());
    EXPECT_EQ(9877 , Initializer::getRCPort());
    EXPECT_EQ("127.0.0.1" , Initializer::getSelfIP());
}