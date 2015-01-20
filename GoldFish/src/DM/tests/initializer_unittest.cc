#include <string.h>

#include <DM/Initializer.h>

#include "gtest/gtest.h"

TEST(InitializerTest , INITTest)
{
    Initializer initializer;
    char* config[2] = {"test" , "-c /home/wuyu/GoldFish/src/DM/tests/test.lua"};
    EXPECT_EQ(0 , initializer.init(2 , config) );
    EXPECT_EQ(45678 , initializer.getOptions().getDCPort());
}