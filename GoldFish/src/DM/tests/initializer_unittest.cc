#include <string.h>

#include <DM/Initializer.h>

#include "gtest/gtest.h"

Initializer g_Initializer;

TEST(InitializerTest , INITTest)
{
    char* config[2] = {"test" , "-c /home/wuyu/Goldfish/GoldFish/src/DM/tests/test.lua"};
    EXPECT_EQ(0 , g_Initializer.init(2 , config) );
    EXPECT_EQ(45678 , g_Initializer.getOptions().getDCPort());
}