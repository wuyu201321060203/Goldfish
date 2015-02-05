#include <DM/ConfigLoader.h>
#include "../lua/fflua_type.h"

#include "gtest/gtest.h"

TEST(ConfigLoaderTest , LoadConfigTest)
{
    Options options;
    ConfigLoader loader;
    loader.setConfigFilePath("/home/wuyu/Goldfish/GoldFish/src/DM/tests/test.lua");
    loader.loadConfig(options);
    EXPECT_EQ(Master , options.getRole());
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