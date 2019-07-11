#include <gtest/gtest.h>

#include "baseline/semi_slow.hpp"
#include "fenwick_tree.hpp"
#include "segtree_semi.hpp"


template<typename Rq, typename RqRef>
class update_tester
{
    Rq rq;
    RqRef rq_ref;

    using value_type = typename Rq::value_type;

public:
    explicit update_tester(const std::vector<value_type>& xs) : rq(xs), rq_ref(xs)
    {
        assert_against_reference();
    }

    void assert_against_reference()
    {
        EXPECT_EQ(rq.size(), rq_ref.size());
        EXPECT_EQ(rq.empty(), rq_ref.empty());

        for(int i = 0; i < rq.size(); i++) {
            for(int j = i + 1; j <= rq.size(); j++) {
                if(std::is_floating_point<value_type>::value) {
                    ASSERT_FLOAT_EQ(rq.get(i, j), rq_ref.get(i, j)) << "(i, j) = (" << i << ", " << j << ")";
                }
                else {
                    ASSERT_EQ(rq.get(i, j), rq_ref.get(i, j)) << "(i, j) = (" << i << ", " << j << ")";
                }
            }
        }
    }

    void set_call(const size_t i, const value_type& x)
    {
        rq.set(i, x);
        rq_ref.set(i, x);

        assert_against_reference();
    }

    void set_handle(const size_t i, const value_type& x)
    {
        rq[i] = x;
        rq_ref[i] = x;

        assert_against_reference();
    }

    void add_handle(const size_t i, const value_type& x)
    {
        rq[i] += x;
        rq_ref[i] += x;

        assert_against_reference();
    }
};


std::vector<int> xs_small = { -11, 9, 13, 24, -1, 23, 5, 11, 18, 18, -2, 16, 18, 3, 21, -10, 13, -3, 25, 22, -10, 1, 6, 16, 0 };
std::vector<std::pair<size_t, int>> xs_updates = {
        { 10, -11 },
        { 13, -1 },
        { 11, 0 },
        { 13, 7 },
        { 0, 23 },
        { 2, -2 },
        { 1, 11 },
        { 1, 14 },
        { 11, 14 },
        { 23, 2 },
        { 14, -12 },
        { 24, -5 },
        { 16, -9 },
        { 4, -14 },
        { 18, -17 },
        { 15, 20 },
        { 4, 14 },
        { 7, 11 },
        { 19, 18 },
        { 1, 24 }
};

TEST(PointFenwick, AddRefSet) {
    update_tester<seg::fenwick_tree<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : xs_updates) {
        tester.set_call(p.first, p.second);
    }
}

TEST(PointFenwick, AddRefHandleAssign) {
    update_tester<seg::fenwick_tree<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : xs_updates) {
        tester.set_handle(p.first, p.second);
    }
}

TEST(PointFenwick, AddRefHandleAdd) {
    update_tester<seg::fenwick_tree<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : xs_updates) {
        tester.add_handle(p.first, p.second);
    }
}

TEST(PointSegtree, AddRefSet) {
    update_tester<seg::segtree_semi<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : xs_updates) {
        tester.set_call(p.first, p.second);
    }
}

TEST(PointSegtree, AddRefHandleAssign) {
    update_tester<seg::segtree_semi<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : xs_updates) {
        tester.set_handle(p.first, p.second);
    }
}

TEST(PointSegtree, AddRefHandleAdd) {
    update_tester<seg::segtree_semi<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : xs_updates) {
        tester.add_handle(p.first, p.second);
    }
}
