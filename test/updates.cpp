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

    void add_call(const size_t i, const size_t j, const value_type& x)
    {
        rq.add(i, j, x);
        rq_ref.add(i, j, x);

        assert_against_reference();
    }

    void set_handle(const size_t i, const size_t j, const value_type& x)
    {
        rq[{i, j}] = x;
        rq_ref[{i, j}] = x;

        assert_against_reference();
    }

    void add_handle(const size_t i, const size_t j, const value_type& x)
    {
        rq[{i, j}] += x;
        rq_ref[{i, j}] += x;

        assert_against_reference();
    }
};


std::vector<int> xs_small = { -11, 9, 13, 24, -1, 23, 5, 11, 18, 18, -2, 16, 18, 3, 21, -10, 13, -3, 25, 22, -10, 1, 6, 16, 0 };
std::vector<std::pair<size_t, int>> us_point = {
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
std::vector<std::tuple<size_t, size_t, int>> us_range = {
        { 10, 13, -11 },
        { 13, 20, -1 },
        { 11, 22, 0 },
        { 13, 22, 7 },
        { 0, 3, 23 },
        { 2, 12, -2 },
        { 1, 10, 11 },
        { 1, 16, 14 },
        { 11, 25, 14 },
        { 23, 25, 2 },
        { 14, 15, -12 },
        { 24, 25, -5 },
        { 16, 20, -9 },
        { 4, 9, -14 },
        { 18, 24, -17 },
        { 15, 24, 20 },
        { 4, 24, 14 },
        { 7, 18, 11 },
        { 19, 22, 18 },
        { 1, 23, 24 }
};

TEST(PointFenwick, AddRefSet) {
    update_tester<seg::fenwick_tree<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : us_point) {
        tester.set_call(p.first, p.second);
    }
}

TEST(PointFenwick, AddRefHandleAssign) {
    update_tester<seg::fenwick_tree<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : us_point) {
        tester.set_handle(p.first, p.second);
    }
}

TEST(PointFenwick, AddRefHandleAdd) {
    update_tester<seg::fenwick_tree<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : us_point) {
        tester.add_handle(p.first, p.second);
    }
}

TEST(PointSegtree, AddRefSet) {
    update_tester<seg::segtree_sum<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : us_point) {
        tester.set_call(p.first, p.second);
    }
}

TEST(PointSegtree, AddRefHandleAssign) {
    update_tester<seg::segtree_sum<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : us_point) {
        tester.set_handle(p.first, p.second);
    }
}

TEST(PointSegtree, AddRefHandleAdd) {
    update_tester<seg::segtree_sum<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : us_point) {
        tester.add_handle(p.first, p.second);
    }
}

TEST(RangeFenwick, AddRefCall) {
    update_tester<seg::fenwick_tree<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : us_range) {
//        tester.add_call(std::get<0>(p), std::get<1>(p), std::get<2>(p));
        FAIL() << "Not implemented";
    }
}

TEST(RangeFenwick, SetRefHandle) {
    update_tester<seg::fenwick_tree<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : us_range) {
//        tester.set_handle(std::get<0>(p), std::get<1>(p), std::get<2>(p));
        FAIL() << "Not implemented";
    }
}

TEST(RangeFenwick, AddRefHandle) {
    update_tester<seg::fenwick_tree<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : us_range) {
//        tester.add_handle(std::get<0>(p), std::get<1>(p), std::get<2>(p));
        FAIL() << "Not implemented";
    }
}

TEST(RangeSegtree, AddRefCall) {
    update_tester<seg::segtree_sum<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : us_range) {
        tester.add_call(std::get<0>(p), std::get<1>(p), std::get<2>(p));
    }
}

TEST(RangeSegtree, SetRefHandle) {
    update_tester<seg::segtree_sum<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : us_range) {
//        tester.set_handle(std::get<0>(p), std::get<1>(p), std::get<2>(p));
        FAIL() << "Not implemented";
    }
}

TEST(RangeSegtree, AddRefHandle) {
    update_tester<seg::segtree_sum<int>, seg::baseline::semi_slow<int>> tester(xs_small);

    for(const auto& p : us_range) {
//        tester.add_handle(std::get<0>(p), std::get<1>(p), std::get<2>(p));
        FAIL() << "Not implemented";
    }
}
