#include <cmath>

#include <gtest/gtest.h>

#include "util/util.hpp"

using namespace seg;

TEST(MathUtil, Log2) {
    EXPECT_EQ(util::log2(0), 0);
    EXPECT_EQ(util::log2(1), 0);
    EXPECT_EQ(util::log2(2), 1);
    EXPECT_EQ(util::log2(3), 1);
    EXPECT_EQ(util::log2(4), 2);
    EXPECT_EQ(util::log2(5), 2);
    EXPECT_EQ(util::log2(31), 4);
    EXPECT_EQ(util::log2(32), 5);
    EXPECT_EQ(util::log2(33), 5);

    EXPECT_EQ(util::log2((1U << 15U) - 1), 14);
    EXPECT_EQ(util::log2(1U << 15U), 15);
    EXPECT_EQ(util::log2((1U << 15U) + 1), 15);
}

TEST(MathUtil, IsPower2) {
    EXPECT_TRUE(util::is_power2(0));
    EXPECT_TRUE(util::is_power2(4));
    EXPECT_TRUE(util::is_power2(65536));
    EXPECT_TRUE(util::is_power2(1U << 17U));
    EXPECT_TRUE(util::is_power2(1ULL << 33U));

    EXPECT_FALSE(util::is_power2(3));
    EXPECT_FALSE(util::is_power2(10));
    EXPECT_FALSE(util::is_power2(72531));
    EXPECT_FALSE(util::is_power2((1U << 17U) / 3));
    EXPECT_FALSE(util::is_power2(3U << 17U));
    EXPECT_FALSE(util::is_power2((1ULL << 37U) + 19));
    EXPECT_FALSE(util::is_power2((1ULL << 37U) + (1ULL << 27U)));
}

TEST(MathUtil, SqrtCeil) {
    const std::vector<size_t> xs = { 1, 4, 7, 8, 9,
                                     63, 64, 65,
                                     199 * 199 - 37, 199 * 199, 199 * 199 + 9,
                                     (1U << 17U) - 1, 1U << 17U, (1U << 17U) + 1,
                                     (1ULL << 43U) - 999, 1ULL << 43U, (1ULL << 43U) + 999 };

    for(const size_t x : xs) {
        EXPECT_EQ(util::sqrt_ceil(x), (size_t)std::ceil(std::sqrt(x))) << x;
    }
}
