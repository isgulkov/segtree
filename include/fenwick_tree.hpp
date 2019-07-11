
#ifndef SEGTREE_FENWICK_TREE_HPP
#define SEGTREE_FENWICK_TREE_HPP

#include <vector>
#include <cassert>

#include "util/functions.hpp"
#include "util/_elem_handle.hpp"

namespace seg {

template<typename T, typename Group = fx::addition<T>>
class fenwick_tree
{
public:
//    using index_type = size_t;
    using value_type = T;

private:
    std::vector<value_type> xs;

public:
    fenwick_tree() = default;

    explicit fenwick_tree(const std::vector<value_type>& xs) : fenwick_tree(xs.cbegin(), xs.cend()) { }

    template <typename InputIt>
    fenwick_tree(const InputIt it_begin, const InputIt it_end) : xs(it_end - it_begin, Group::id())
    {
        for(size_t i = 0; i < xs.size(); i++) {
            add(i, it_begin[i]);
        }
    }

    size_t size() const
    {
        return xs.size();
    }

    bool empty() const
    {
        return xs.empty();
    }

private:
    value_type get_upto(size_t i_end) const
    {
        if(!i_end) {
            return Group::id();
        }

        value_type result = xs[i_end - 1];

        while(i_end -= (i_end & -i_end)) {
            result = Group::add(result, xs[i_end - 1]);
        }

        return result;
    }

public:
    value_type get(const size_t i_begin, const size_t i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= xs.size());
        assert(i_begin < i_end);

        return Group::subtract(get_upto(i_end), get_upto(i_begin));
    }

    value_type operator[](const size_t i) const
    {
        assert(i >= 0);
        assert(i < xs.size());

        return get(i, i + 1);
    }

    void add(size_t i, const value_type& delta)
    {
        assert(i >= 0);
        assert(i < xs.size());

        // TODO: use this directly in elem_handle's operator+=?

        for(; i < xs.size(); i = i | (i + 1)) {
            xs[i] = Group::add(xs[i], delta);
        }
    }

    void set(const size_t i, const value_type& x)
    {
        assert(i >= 0);
        assert(i < xs.size());

        add(i, Group::subtract(x, operator[](i)));
    }

private:
    using elem_handle = util::_elem_handle<fenwick_tree>;

public:
    elem_handle operator[](const size_t i)
    {
        assert(i >= 0);
        assert(i < xs.size());

        return { *this, i };
    }
};

}

#endif //SEGTREE_FENWICK_TREE_HPP
