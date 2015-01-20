#include <DM/ConfigLoader.h>
#include "../lua/fflua_type.h"

#include "gtest/gtest.h"

TEST(ConfigLoaderTest , LoadConfigTest)
{
    Options options;
    ConfigLoader loader;
    loader.setConfigFilePath("/home/wuyu/GoldFish/src/DM/tests/test.lua");
    loader.loadConfig(options);
    EXPECT_EQ("1.1.1.1" , options.getRasIp());
    EXPECT_EQ(9877 , options.getRasPort());
    EXPECT_EQ(Master , options.getRole());
    EXPECT_EQ("ddcnmb" , options.getDbUserName());
    EXPECT_EQ("passwd" , options.getDbPasswd());
    EXPECT_EQ("test" , options.getDbInstance());
    EXPECT_EQ(12345 , options.getCliPort());
    EXPECT_EQ(45678 , options.getDCPort());
}

TEST(ConfigLoaderTest , BadPathTest)
{
    ConfigLoader loader;
    Options options;
    loader.setConfigFilePath("xxx");
    EXPECT_THROW
    (
        {loader.loadConfig(options);},
        ff::lua_exception_t
    );
}