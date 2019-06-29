#include <functional>

#include <gtest/gtest.h>

#include "baseline/rmq_slow.hpp"
#include "rmq_compact.hpp"
#include "rmq_fast.hpp"
#include "rmq_cartesian.hpp"

// TODO: consider dropping this crap in favour of Catch2?
// TODO: check if move and copy assignments work

TEST(RmqCompact, Empty) {
    EXPECT_TRUE(seg::rmq_compact<int>().empty());
}

TEST(RmqFast, Empty) {
    EXPECT_TRUE(seg::rmq_fast<int>().empty());
}

TEST(RmqCartesian, Empty) {
    EXPECT_TRUE(seg::rmq_cartesian<int>().empty());
}

template<typename Rmq, typename RmqRef, typename T>
void assert_against_reference(const std::vector<T>& xs)
{
    RmqRef rmq_ref(xs);
    Rmq rmq(xs);

    EXPECT_EQ(rmq.size(), xs.size());
    EXPECT_FALSE(rmq.empty());

    for(int i = 0; i < xs.size(); i++) {
        for(int j = i + 1; j < xs.size(); j++) {
            ASSERT_EQ(rmq.get(i, j), rmq_ref.get(i, j)) << "(i, j) = (" << i << ", " << j << ")";
        }
    }
}

std::vector<int> xs_small = { -11, 9, 13, 24, -1, 23, 5, 11, 18, 18, -2, 16, 18, 3, 21, -10, 13, -3, 25, 22, -10, 1, 6, 16, 0 };
std::vector<int> ys_small = { 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0 };
std::vector<double> zs = { 0.23562345900933712, 0.921194171139331, -0.0927100101238203, 0.5314802586043694,
                           -0.7494946492240331, -0.8944356230293231, 0.3469770608692895, -0.9862556258852617,
                           0.3723187193230091, -0.3749033717667052, 0.46787827703764706, -0.9965849031542593,
                           -0.5455637708111314, 0.9757643830812546, 0.9398363132695124 };

TEST(RmqCompact, MinReferenceInts) {
    assert_against_reference<seg::rmq_compact<int>, seg::baseline::rmq_slow<int>, int>(xs_small);
}

TEST(RmqCompact, MinReference01) {
    assert_against_reference<seg::rmq_compact<int>, seg::baseline::rmq_slow<int>, int>(ys_small);
}

TEST(RmqCompact, MinReferenceFloat) {
    assert_against_reference<seg::rmq_compact<double>, seg::baseline::rmq_slow<double>, double>(zs);
}

TEST(RmqCompact, MaxReferenceInts) {
    assert_against_reference<seg::rmq_compact<int, std::greater<>>, seg::baseline::rmq_slow<int, std::greater<>>, int>(xs_small);
}

TEST(RmqCompact, MaxReference01) {
    assert_against_reference<seg::rmq_compact<int, std::greater<>>, seg::baseline::rmq_slow<int, std::greater<>>, int>(ys_small);
}

TEST(RmqCompact, MaxReferenceFloat) {
    assert_against_reference<seg::rmq_compact<double, std::greater<>>, seg::baseline::rmq_slow<double, std::greater<>>, double>(zs);
}

TEST(RmqFast, MinReferenceInts) {
    assert_against_reference<seg::rmq_fast<int>, seg::baseline::rmq_slow<int>, int>(xs_small);
}

TEST(RmqFast, MinReference01) {
    assert_against_reference<seg::rmq_fast<int>, seg::baseline::rmq_slow<int>, int>(ys_small);
}

TEST(RmqFast, MinReferenceFloat) {
    assert_against_reference<seg::rmq_fast<double>, seg::baseline::rmq_slow<double>, double>(zs);
}

TEST(RmqFast, MaxReferenceInts) {
    assert_against_reference<seg::rmq_fast<int, std::greater<>>, seg::baseline::rmq_slow<int, std::greater<>>, int>(xs_small);
}

TEST(RmqFast, MaxReference01) {
    assert_against_reference<seg::rmq_fast<int, std::greater<>>, seg::baseline::rmq_slow<int, std::greater<>>, int>(ys_small);
}

TEST(RmqFast, MaxReferenceFloat) {
    assert_against_reference<seg::rmq_fast<double, std::greater<>>, seg::baseline::rmq_slow<double, std::greater<>>, double>(zs);
}

TEST(RmqCartesian, MinReferenceInts) {
    assert_against_reference<seg::rmq_cartesian<int>, seg::baseline::rmq_slow<int>, int>(xs_small);
}

TEST(RmqCartesian, MinReference01) {
    assert_against_reference<seg::rmq_cartesian<int>, seg::baseline::rmq_slow<int>, int>(ys_small);
}

TEST(RmqCartesian, MinReferenceFloat) {
    assert_against_reference<seg::rmq_cartesian<double>, seg::baseline::rmq_slow<double>, double>(zs);
}

TEST(RmqCartesian, MaxReferenceInts) {
    assert_against_reference<seg::rmq_cartesian<int, std::greater<>>, seg::baseline::rmq_slow<int, std::greater<>>, int>(xs_small);
}

TEST(RmqCartesian, MaxReference01) {
    assert_against_reference<seg::rmq_cartesian<int, std::greater<>>, seg::baseline::rmq_slow<int, std::greater<>>, int>(ys_small);
}

TEST(RmqCartesian, MaxReferenceFloat) {
    assert_against_reference<seg::rmq_cartesian<double, std::greater<>>, seg::baseline::rmq_slow<double, std::greater<>>, double>(zs);
}
