#include <gtest/gtest.h>

#include <random>

#include "baseline/rq_mode_slow.hpp"
#include "rq_mode_fast.hpp"

TEST(RqModeFast, Empty) {
    EXPECT_TRUE(seg::rq_mode_fast<int>().empty());
}

template<typename Rq, typename RqRef, typename T>
void assert_against_reference(const std::vector<T>& xs)
{
    RqRef rq_ref(xs);
    Rq rq(xs);

    EXPECT_EQ(rq.size(), xs.size());
    EXPECT_FALSE(rq.empty());

    for(int i = 0; i < xs.size(); i++) {
        for(int j = i + 1; j < xs.size(); j++) {
            const auto v = rq.get(i, j);
            const auto v_ref = rq_ref.get(i, j);

//            ASSERT_EQ(v.has_value(), v_ref.has_value()) << "(i, j) = (" << i << ", " << j << ")";;

            if(v.has_value() && v_ref.has_value()) {
                ASSERT_EQ(v.value(), v_ref.value()) << "(i, j) = (" << i << ", " << j << ")";
            }
        }
    }
}

std::vector<int> xs_small = { -11, 9, 13, 24, -1, 23, 5, 11, 18, 18, -2, 16, 18, 3, 21, -10, 13, -3, 25, 22, -10, 1, 6, 16, 0 };
std::vector<int> ys_small = { 1, -1, -1, 1, 1, 1, 1, -1, -1, 1, 1, 1, -1, 1, -1 };


TEST(RqModeFast, IntsRefMany) {
    assert_against_reference<seg::rq_mode_fast<int>, seg::baseline::rq_mode_slow<int>, int>(xs_small);
}

TEST(RqModeFast, IntsRefFew) {
    assert_against_reference<seg::rq_mode_fast<int>, seg::baseline::rq_mode_slow<int>, int>(ys_small);
}
