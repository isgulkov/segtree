
#ifndef SEGTREE_SEGTREE_SEMI_HPP
#define SEGTREE_SEGTREE_SEMI_HPP

#include <vector>
#include <cassert>
#include <functional>

#include "util.hpp"

namespace seg {

template<typename T, typename Add = std::plus<T>>
class segtree_semi
{
    Add add{ };

    size_t n = 0;
    std::vector<T> xs_nodes;

    template <typename InputIt>
    T build_xs_min(const InputIt it_begin, const InputIt it_end, const size_t i_node)
    {
        if(it_begin + 1 == it_end) {
            return xs_nodes[i_node] = *it_begin;
        }

        const InputIt it_mid = it_begin + (it_end - it_begin + 1) / 2;

        const T l_value = build_xs_min(it_begin, it_mid, (i_node + 1) * 2 - 1);
        const T r_value = build_xs_min(it_mid, it_end, (i_node + 1) * 2);

        return xs_nodes[i_node] = add(l_value, r_value);
    }

public:
    segtree_semi() = default;

    explicit segtree_semi(const std::vector<T>& xs) : segtree_semi(xs.cbegin(), xs.cend()) { }

    template <typename InputIt>
    segtree_semi(const InputIt it_begin, const InputIt it_end) : n(it_end - it_begin),
                                                                xs_nodes(2 << (util::log2(n - 1) + 1))
    {
        // `xs_min` size is rounded up to the next power of two, where the tree would be saturated

        build_xs_min(it_begin, it_end, 0);
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
            return xs_nodes[i_node];
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

            const T l_value = get(i_begin, i_mid, i_left, i_mid, (i_node + 1) * 2 - 1);
            const T r_value = get(i_mid, i_end, i_mid, i_right, (i_node + 1) * 2);

            return add(l_value, r_value);
        }
    }

public:
    T get(const size_t i_begin, const size_t i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= n);

        if(i_begin >= i_end) {
            return T();
        }

        return get(i_begin, i_end, 0, n, 0);
    }

private:
    void update(const size_t i, const T& x, const size_t i_left, const size_t i_right, const size_t i_node)
    {
        if(i_left == i && i_right == i + 1) {
            xs_nodes[i_node] = x;

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
        const T& l_value = xs_nodes[(i_node + 1) * 2 - 1];
        const T& r_value = xs_nodes[(i_node + 1) * 2];

        xs_nodes[i_node] = add(l_value, r_value);
    }

public:
    void set(const size_t i, const T& x)
    {
        assert(i >= 0);
        assert(i < n);

        update(i, x, 0, n, 0);
    }
};

namespace {

template<typename T, typename Compare = std::less<T>>
class _min_semi
{
    Compare less{ };

public:
    T operator()(const T& a, const T& b) const
    {
        return less(a, b) ? a : b;
    }
};

}

template<typename T, typename Compare = std::less<T>>
struct segtree_min : segtree_semi<T, _min_semi<T, Compare>>
{
    using segtree_semi<T, _min_semi<T, Compare>>::segtree_semi;
};

}

#endif //SEGTREE_SEGTREE_SEMI_HPP
