
#ifndef SEGTREE_RMQ_COMPACT_HPP
#define SEGTREE_RMQ_COMPACT_HPP

#include <vector>
#include <cassert>
#include <functional>

#include "util.hpp"

namespace seg {

template<typename T, typename Compare = std::less<T>>
class rmq_compact
{
    const Compare less{ };

    const size_t n = 0;
    std::vector<T> xs_min;

    static T build_xs_min(const typename std::vector<T>::const_iterator it_begin,
                          const typename std::vector<T>::const_iterator it_end,
                          std::vector<T>& xs_min, const size_t i_node,
                          const Compare less = Compare())
    {
        if(it_begin + 1 == it_end) {
            return xs_min[i_node] = *it_begin;
        }

        const auto x_mid = it_begin + (it_end - it_begin + 1) / 2;

        const T l_min = build_xs_min(it_begin, x_mid, xs_min, (i_node + 1) * 2 - 1);
        const T r_min = build_xs_min(x_mid, it_end, xs_min, (i_node + 1) * 2);

        return xs_min[i_node] = less(l_min, r_min) ? l_min : r_min;
    }

public:
    explicit rmq_compact(const std::vector<T>& xs) : rmq_compact(xs.begin(), xs.end()) { }

    template <typename InputIt>
    rmq_compact(InputIt it_begin, const InputIt it_end) : n(it_end - it_begin),
                                                          xs_min(2 << (util::log2((it_end - it_begin) - 1) + 1))
    {
        // `xs_min` size is rounded up to the next power of two, where the tree would be saturated

        build_xs_min(it_begin, it_end, xs_min, 0);

//        for(const T x : xs_min) {
//            std::cout << x << " ";
//        }
//        std::cout << std::endl;
    }

    size_t size() const
    {
        return n;
    }

    bool empty() const
    {
        return n == 0;
    }

private:
    T get(const size_t i_begin, const size_t i_end,
          const size_t i_left, const size_t i_right, const size_t i_node) const
    {
        if(i_begin == i_left && i_end == i_right) {
            return xs_min[i_node];
        }

        const size_t i_mid = i_left + (i_right - i_left + 1) / 2;

        if(i_end <= i_mid) {
            return get(i_begin, i_end, i_left, i_mid, (i_node + 1) * 2 - 1);
        }
        else if(i_mid <= i_begin) {
            return get(i_begin, i_end, i_mid, i_right, (i_node + 1) * 2);
        }
        else {
            // TODO: tail-recursive implementation?

            const T l_min = get(i_begin, i_mid, i_left, i_mid, (i_node + 1) * 2 - 1);
            const T r_min = get(i_mid, i_end, i_mid, i_right, (i_node + 1) * 2);

            return less(l_min, r_min) ? l_min : r_min;
        }
    }

public:
    T get(const size_t i_begin, const size_t i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= n);
        assert(i_begin < i_end);

        return get(i_begin, i_end, 0, n, 0);
    }

    size_t index(const size_t i_begin, const size_t i_end) const
    {
        // This has to be doable in a DRY way
    }

private:
    void update(const size_t i, const T& x, const size_t i_left, const size_t i_right, const size_t i_node)
    {
        if(i_left == i && i_right == i + 1) {
            xs_min[i_node] = x;

            return;
        }

        const size_t i_mid = i_left + (i_right - i_left + 1) / 2;

        if(i < i_mid) {
            update(i, x, i_left, i_mid, (i_node + 1) * 2 - 1);
        }
        else {
            update(i, x, i_mid, i_right, (i_node + 1) * 2);
        }

        // TODO: use return values
        const T& l_min = xs_min[(i_node + 1) * 2 - 1];
        const T& r_min = xs_min[(i_node + 1) * 2];

        xs_min[i_node] = less(l_min, r_min) ? l_min : r_min;
    }

public:
    void set(const size_t i, const T& x)
    {
        assert(i >= 0);
        assert(i < n);

        update(i, x, 0, n, 0);
    }
};

}

#endif //SEGTREE_RMQ_COMPACT_HPP
