#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>

#include "gtest/gtest.h"

#include <DM/Config.h>
#include <DM/CryptographicService.h>
#include <DM/DesEcbService.h>

TEST(DesEcbServiceTest , actionTest)
{
    STDSTR testStr("hello world");
    STDSTR dstStr(testStr);
    dstStr.append(5 , 5);
    boost::shared_ptr<CryptographicService> actioner(new DesEcbService);
    STDSTR ret = actioner->encrypt(testStr);
    std::cout << "after encrypt" << ret << "\n";
    EXPECT_EQ(dstStr , actioner->decode(ret));
}