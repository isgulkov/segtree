#include <gtest/gtest.h>

#include "util/util.hpp"

using namespace seg::util;

TEST(MathUtil, Log2) {
    EXPECT_EQ(log2(0), 0);
    EXPECT_EQ(log2(1), 0);
    EXPECT_EQ(log2(2), 1);
    EXPECT_EQ(log2(3), 1);
    EXPECT_EQ(log2(4), 2);
    EXPECT_EQ(log2(5), 2);
    EXPECT_EQ(log2(31), 4);
    EXPECT_EQ(log2(32), 5);
    EXPECT_EQ(log2(33), 5);

    EXPECT_EQ(log2((1U << 15U) - 1), 14);
    EXPECT_EQ(log2(1U << 15U), 15);
    EXPECT_EQ(log2((1U << 15U) + 1), 15);
}

TEST(MathUtil, IsPower2) {
    EXPECT_TRUE(is_power2(0));
    EXPECT_TRUE(is_power2(4));
    EXPECT_TRUE(is_power2(65536));
    EXPECT_TRUE(is_power2(1U << 17U));
    EXPECT_TRUE(is_power2(1ULL << 33U));

    EXPECT_FALSE(is_power2(3));
    EXPECT_FALSE(is_power2(10));
    EXPECT_FALSE(is_power2(72531));
    EXPECT_FALSE(is_power2((1U << 17U) / 3));
    EXPECT_FALSE(is_power2(3U << 17U));
    EXPECT_FALSE(is_power2((1ULL << 37U) + 19));
    EXPECT_FALSE(is_power2((1ULL << 37U) + (1ULL << 27U)));
}
