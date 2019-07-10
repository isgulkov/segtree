#include <type_traits>

#include <gtest/gtest.h>

#include "baseline/semi_slow.hpp"
#include "rq_group.hpp"
#include "segtree_semi.hpp"
#include "fenwick_tree.hpp"

TEST(RqgStatic, Empty) {
    EXPECT_TRUE(seg::rq_group<int>().empty());
}

TEST(RqgSegtree, Empty) {
    EXPECT_TRUE(seg::segtree_semi<int>().empty());
}

TEST(RqgFenwick, Empty) {
    EXPECT_TRUE(seg::fenwick_tree<int>().empty());
}

template<typename Rq, typename RqRef, typename T>
void assert_against_reference(const std::vector<T>& xs)
{
    RqRef rq_ref(xs);
    Rq rq(xs);

    EXPECT_EQ(rq.size(), xs.size());
    EXPECT_FALSE(rq.empty());

    for(int i = 0; i < xs.size(); i++) {
        for(int j = i + 1; j <= xs.size(); j++) {
            if(std::is_floating_point<T>::value) {
                ASSERT_FLOAT_EQ(rq.get(i, j), rq_ref.get(i, j)) << "(i, j) = (" << i << ", " << j << ")";
            }
            else {
                ASSERT_EQ(rq.get(i, j), rq_ref.get(i, j)) << "(i, j) = (" << i << ", " << j << ")";
            }
        }
    }
}

std::vector<int> xs_small = { -11, 9, 13, 24, -1, 23, 5, 11, 18, 18, -2, 16, 18, 3, 21, -10, 13, -3, 25, 22, -10, 1, 6, 16, 0 };
std::vector<int> ys_small = { 1, -1, -1, 1, 1, 1, 1, -1, -1, 1, 1, 1, -1, 1, -1 };
std::vector<int> xs_incs = ([]() {
    std::vector<int> xs;
    for(int i = -10; i <= 10; i++) xs.push_back(i);
    return xs;
})();
std::vector<double> zs = { 0.23562345900933712, 0.921194171139331, -0.0927100101238203, 0.5314802586043694,
                           -0.7494946492240331, -0.8944356230293231, 0.3469770608692895, -0.9862556258852617,
                           0.3723187193230091, -0.3749033717667052, 0.46787827703764706, -0.9965849031542593,
                           -0.5455637708111314, 0.9757643830812546, 0.9398363132695124 };

// TODO: other group operators for each one!

TEST(RqgStatic, AddRefSmall) {
    assert_against_reference<seg::rq_group<int>, seg::baseline::semi_slow<int>, int>(xs_small);
}

TEST(RqgStatic, AddRef01) {
    assert_against_reference<seg::rq_group<int>, seg::baseline::semi_slow<int>, int>(ys_small);
}

TEST(RqgStatic, AddRefIncs) {
    assert_against_reference<seg::rq_group<int>, seg::baseline::semi_slow<int>, int>(xs_incs);
}

TEST(RqgStatic, AddRefFloat) {
    assert_against_reference<seg::rq_group<double>, seg::baseline::semi_slow<double>, double>(zs);
}

TEST(RqgStatic, MulRefFloat) {
    assert_against_reference<seg::rq_group<double, seg::fx::multiplication<double>>, seg::baseline::semi_slow<double, seg::fx::multiplication<double>>, double>(zs);
}


TEST(RqgSegtree, AddRefSmall) {
    assert_against_reference<seg::segtree_semi<int>, seg::baseline::semi_slow<int>, int>(xs_small);
}

TEST(RqgSegtree, AddRef01) {
    assert_against_reference<seg::segtree_semi<int>, seg::baseline::semi_slow<int>, int>(ys_small);
}

TEST(RqgSegtree, AddRefIncs) {
    assert_against_reference<seg::segtree_semi<int>, seg::baseline::semi_slow<int>, int>(xs_incs);
}

TEST(RqgSegtree, AddRefFloat) {
    assert_against_reference<seg::segtree_semi<double>, seg::baseline::semi_slow<double>, double>(zs);
}

TEST(RqgSegtree, MulRefFloat) {
    assert_against_reference<seg::segtree_semi<double, seg::fx::multiplication<double>>, seg::baseline::semi_slow<double, seg::fx::multiplication<double>>, double>(zs);
}


TEST(RqgFenwick, AddRefSmall) {
    assert_against_reference<seg::fenwick_tree<int>, seg::baseline::semi_slow<int>, int>(xs_small);
}

TEST(RqgFenwick, AddRef01) {
    assert_against_reference<seg::fenwick_tree<int>, seg::baseline::semi_slow<int>, int>(ys_small);
}

TEST(RqgFenwick, AddRefIncs) {
    assert_against_reference<seg::fenwick_tree<int>, seg::baseline::semi_slow<int>, int>(xs_incs);
}

TEST(RqgFenwick, AddRefFloat) {
    assert_against_reference<seg::fenwick_tree<double>, seg::baseline::semi_slow<double>, double>(zs);
}

TEST(RqgFenwick, MulRefFloat) {
    assert_against_reference<seg::fenwick_tree<double, seg::fx::multiplication<double>>, seg::baseline::semi_slow<double, seg::fx::multiplication<double>>, double>(zs);
}
