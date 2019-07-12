
#ifndef SEGTREE_SEMI_SLOW_HPP
#define SEGTREE_SEMI_SLOW_HPP

#include <vector>
#include <cassert>
#include <algorithm>

#include "util/functions.hpp"
#include "util/elem_handle.hpp"
#include "util/range_handle.hpp"

namespace seg::baseline {

template<typename T, typename Semi = fx::addition<T>>
class semi_slow
{
public:
    using index_type = size_t;
    using value_type = T;

private:
    std::vector<value_type> xs;

public:
    semi_slow() = default;

    explicit semi_slow(const std::vector<value_type>& xs) : xs(xs) { }

    template <typename InputIt>
    semi_slow(const InputIt it_begin, const InputIt it_end) : xs(it_begin, it_end) { }

    index_type size() const
    {
        return (index_type)xs.size();
    }

    bool empty() const
    {
        return xs.empty();
    }

public:
    T get(const index_type i_begin, const index_type i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= xs.size());
        assert(i_begin < i_end);

        // TODO: consider returning zero (id) for empty ranges

        value_type result = xs[i_begin];

        for(index_type i = i_begin + 1; i != i_end; i++) {
            result = Semi::add(result, xs[i]);
        }

        return result;
    }

    const value_type& operator[](const index_type i) const
    {
        assert(i >= 0);
        assert(i < xs.size());

        return xs[i];
    }

    void set(const index_type i, const value_type& x)
    {
        assert(i >= 0);
        assert(i < xs.size());

        xs[i] = x;
    }

    util::elem_handle<semi_slow> operator[](const index_type i)
    {
        assert(i >= 0);
        assert(i < xs.size());

        return { *this, i };
    }

    void update(const index_type i, std::function<value_type(const value_type&)> f)
    {
        /**
         * TODO: benchmark the three point update interfaces:
         *  - set(i, EXPR(get(i)));
         *  - modify(i, std::function);
         *  - assignment to an `elem_handle`.
         */

        assert(i >= 0);
        assert(i < xs.size());

        xs[i] = f(xs[i]);
    }

    void set(const index_type i_begin, const index_type i_end, const value_type& x)
    {
        assert(i_begin >= 0);
        assert(i_end <= xs.size());
        assert(i_begin < i_end);

        std::fill(xs.begin() + i_begin, xs.begin() + i_end, x);
    }

    void add(const index_type i_begin, const index_type i_end, const value_type& y)
    {
        assert(i_begin >= 0);
        assert(i_end <= xs.size());
        assert(i_begin < i_end);

        std::transform(xs.begin() + i_begin, xs.begin() + i_end, xs.begin() + i_begin, [&y](const auto& x) {
            return Semi::add(x, y);
        });
    }

    util::range_handle<semi_slow> operator[](const std::pair<index_type, index_type> ix)
    {
        assert(ix.first >= 0);
        assert(ix.second <= xs.size());
        assert(ix.first < ix.secondd);

        return { *this, ix.first, ix.second };
    }
};

}

#endif //SEGTREE_SEMI_SLOW_HPP
