#include <numeric>
#include <gtest/gtest.h>
#include "../src/gcd.h"

TEST(test_01, test_set)
{
    auto lval = 1, rval = 150;
    ASSERT_EQ(gcd(lval,rval),std::gcd(lval, rval));
}

TEST(test_02, test_set)
{
    auto lval = 100, rval = 0;
    ASSERT_EQ(gcd(lval,rval), std::gcd(lval,rval));
}

TEST(test_03, test_set)
{
    auto lval = 5, rval = 25;
    ASSERT_EQ(gcd(lval,rval), std::gcd(lval,rval));
}

TEST(test_04, test_set)
{
    auto lval = 28, rval = -362;
    ASSERT_EQ(gcd(lval,rval), std::gcd(lval,rval));
}

TEST(test_05, test_set)
{
    auto lval = -5, rval = 25;
    ASSERT_EQ(gcd(lval,rval), std::gcd(lval,rval));
}

TEST(test_06, test_set)
{
    auto lval = -5, rval = -25;
    ASSERT_EQ(gcd(lval,rval), std::gcd(lval,rval));
}

TEST(test_07, test_set)
{
    auto lval = 0, rval = -25;
    ASSERT_EQ(gcd(lval,rval), std::gcd(lval,rval));
}

TEST(test_08, test_set)
{
    auto lval = 0, rval = 0;
    ASSERT_EQ(gcd(lval,rval), std::gcd(lval,rval));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}