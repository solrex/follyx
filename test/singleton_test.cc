#include "ooo/singleton.h"

#include <gtest/gtest.h>
#include <glog/logging.h>

using namespace ooo;

TEST(SingletonTest, get)
{
    EXPECT_TRUE(NULL != Singleton<int>::get());
    (*Singleton<int>::get()) = 1;
    EXPECT_EQ(1, *Singleton<int>::get());
}
