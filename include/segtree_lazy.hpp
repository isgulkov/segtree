
#ifndef SEGTREE_SEGTREE_LAZY_HPP
#define SEGTREE_SEGTREE_LAZY_HPP

#include <vector>
#include <cassert>

#include "util/functions.hpp"
#include "util/util.hpp"
#include "util/elem_handle.hpp"
#include "util/range_handle.hpp"

namespace seg {

template<typename T, typename Semi = fx::addition<T>>
class segtree_lazy
{
public:
    using index_type = size_t;
    using value_type = T;

    // TODO!: Implement the lazy version non-recursively (share as much code as possible with the regular one).

private:
    index_type n = 0;

    mutable std::vector<value_type> xs_nodes;
    mutable std::vector<value_type> ds_nodes;

    template <typename InputIt>
    static const value_type& build_nodes(std::vector<value_type>& xs_nodes, const index_type i_node,
                                         const InputIt it_begin, const InputIt it_end)
    {
        const size_t l_node = it_end - it_begin;

        if(l_node == 1) {
            return xs_nodes[i_node] = *it_begin;
        }

        const InputIt it_mid = it_begin + (l_node + 1) / 2;

        const value_type& v_left = build_nodes(xs_nodes, i_node * 2, it_begin, it_mid);
        const value_type& v_right = build_nodes(xs_nodes, i_node * 2 + 1, it_mid, it_end);

        return xs_nodes[i_node] = Semi::add(v_left, v_right);
    }

public:
    segtree_lazy() = default;

    explicit segtree_lazy(const std::vector<value_type>& xs) : segtree_lazy(xs.cbegin(), xs.cend()) { }

    template <typename InputIt>
    segtree_lazy(InputIt it_begin, const InputIt it_end) : n(it_end - it_begin)
    {
        xs_nodes.resize(4 * n);

        build_nodes(xs_nodes, 1, it_begin, it_end);

        ds_nodes.resize(xs_nodes.size() / 2, Semi::id());
    }

    index_type size() const
    {
        return n;
    }

    bool empty() const
    {
        return n == 0;
    }

private:
    value_type _get(const index_type i_begin, const index_type i_end,
                    const index_type in_begin, const index_type in_end, const index_type i_node) const
    {
        if(i_begin == in_begin && i_end == in_end) {
            return xs_nodes[i_node];
        }

        const index_type i_mid = in_begin + (in_end - in_begin + 1) / 2;

        if(i_end <= i_mid) {
            return _get(i_begin, i_end, in_begin, i_mid, i_node * 2);
        }
        else if(i_mid <= i_begin) {
            return _get(i_begin, i_end, i_mid, in_end, i_node * 2 + 1);
        }

        const value_type v_left = _get(i_begin, i_mid, in_begin, i_mid, i_node * 2);
        const value_type v_right = _get(i_mid, i_end, i_mid, in_end, i_node * 2 + 1);

        return Semi::add(v_left, v_right);
    }

public:
    value_type get(const index_type i_begin, const index_type i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= n);
        assert(i_begin < i_end);

        return _get(i_begin, i_end, 0, n, 1);
    }

    value_type operator[](const index_type i) const {
        assert(i >= 0);
        assert(i < n);

        return get(i, i + 1);
    }

private:
    void _set(index_type i, const value_type& x, const index_type in_begin, const index_type in_end, const index_type i_node)
    {
        if(in_begin == i && in_end == i + 1) {
            xs_nodes[i_node] = x;

            return;
        }

        const index_type i_mid = in_begin + (in_end - in_begin + 1) / 2;

        if(i < i_mid) {
            _set(i, x, in_begin, i_mid, i_node * 2);
        }
        else {
            _set(i, x, i_mid, in_end, i_node * 2 + 1);
        }

        xs_nodes[i_node] = Semi::add(xs_nodes[i_node * 2], xs_nodes[i_node * 2 + 1]);
    }

public:
    segtree_lazy& set(index_type i, const value_type& x)
    {
        assert(i >= 0);
        assert(i < n);

        _set(i, x, 0, n, 1);

        return *this;
    }

    util::elem_handle<segtree_lazy> operator[](const index_type i)
    {
        assert(i >= 0);
        assert(i < n);

        return { *this, i };
    }

private:
    // ...

public:
    segtree_lazy& set(const index_type i_begin, const index_type i_end, const value_type& x)
    {
        assert(i_begin >= 0);
        assert(i_end <= n);
        assert(i_begin < i_end);

        // TODO!: Replace with proper O(logn) updates.

        for(size_t i = i_begin; i < i_end; i++) {
            set(i, x);
        }

        return *this;
    }

    segtree_lazy& add(const index_type i_begin, const index_type i_end, const value_type& x)
    {
        assert(i_begin >= 0);
        assert(i_end <= n);
        assert(i_begin < i_end);

        // TODO!: Replace with proper O(logn) updates.

        for(size_t i = i_begin; i < i_end; i++) {
            set(i, Semi::add(operator[](i), x));
        }

        return *this;
    }

    util::range_handle<segtree_lazy> operator[](const std::pair<index_type, index_type> ix)
    {
        assert(ix.first >= 0);
        assert(ix.second <= n);
        assert(ix.first < ix.second);

        return { *this, ix.first, ix.second };
    }
};

}

#endif //SEGTREE_SEGTREE_LAZY_HPP
