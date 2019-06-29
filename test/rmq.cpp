#include <gtest/gtest.h>

#include "baseline/rmq_slow.hpp"
#include "rmq_compact.hpp"
#include "rmq_fast.hpp"
#include "rmq_cartesian.hpp"

TEST(RmqEmpty, Empty)
{
    EXPECT_TRUE(seg::rmq_fast<int>().empty());
}

template<typename rmq_t>
class RmqInts : public testing::TestWithParam<std::vector<int>> {};

TYPED_TEST_SUITE_P(RmqInts);

std::vector<int> xs_small = { -11, 9, 13, 24, -1, 23, 5, 11, 18, 18, -2, 16, 18, 3, 21, -10, 13, -3, 25, 22, -10, 1, 6, 16, 0 };
std::vector<int> ys_small = { 12, 16, 22, 11, -4, -9, 4, 0, 9, 2, -10, 5, 8, 3, 8, 23, -3, 25 };
std::vector<int> zs_small = { 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0 };

TYPED_TEST_P(RmqInts, Individuals) {
    const auto& xs = xs_small;

    seg::rmq_fast<int> rmq(xs);

    EXPECT_EQ(rmq.size(), xs.size());
    EXPECT_FALSE(rmq.empty());

    for(int i = 0; i < xs.size(); i++) {
        ASSERT_EQ(rmq.get(i, i + 1), xs[i]);
    }
}

TYPED_TEST_P(RmqInts, Ranges) {
    const auto& xs = ys_small;

    seg::baseline::rmq_slow<int> rmq_s(xs);
    seg::rmq_fast<int> rmq(xs);

    EXPECT_EQ(rmq.size(), xs.size());
    EXPECT_FALSE(rmq.empty());

    for(int i = 0; i < xs.size(); i++) {
        for(int j = i + 1; j < xs.size(); j++) {
            ASSERT_EQ(rmq.get(i, j), rmq_s.get(i, j));
        }
    }
}

REGISTER_TYPED_TEST_SUITE_P(RmqInts, Individuals, Ranges);

using RmqIntTs = ::testing::Types<seg::baseline::rmq_slow<int>, seg::rmq_compact<int>, seg::rmq_fast<int>, seg::rmq_cartesian<int>>;

INSTANTIATE_TYPED_TEST_SUITE_P(Small, RmqInts, RmqIntTs);
