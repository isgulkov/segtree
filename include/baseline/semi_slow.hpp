
#ifndef SEGTREE_SEMI_SLOW_HPP
#define SEGTREE_SEMI_SLOW_HPP

#include <vector>
#include <cassert>

#include "util/functions.hpp"
#include "util/_elem_handle.hpp"

namespace seg::baseline {

template<typename T, typename Semi = fx::addition<T>>
class semi_slow
{
    std::vector<T> xs;

public:
    semi_slow() = default;

    explicit semi_slow(const std::vector<T>& xs) : xs(xs) { }

    template <typename InputIt>
    semi_slow(const InputIt it_begin, const InputIt it_end) : xs(it_begin, it_end) { }

    size_t size() const
    {
        return xs.size();
    }

    bool empty() const
    {
        return xs.empty();
    }

public:
    T get(const size_t i_begin, const size_t i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= xs.size());
        assert(i_begin < i_end);

        // TODO: consider returning zero (id) for empty ranges

        T result = xs[i_begin];

        for(size_t i = i_begin + 1; i != i_end; i++) {
            result = Semi::add(result, xs[i]);
        }

        return result;
    }

    void set(const size_t i, const T& x)
    {
        assert(i >= 0);
        assert(i < xs.size());

        xs[i] = x;
    }

private:
    using elem_handle = util::_elem_handle<semi_slow<T, Semi>, T>;

public:
    const T& operator[](const size_t i) const
    {
        assert(i >= 0);
        assert(i < xs.size());

        return xs[i];
    }

    elem_handle operator[](const size_t i)
    {
        assert(i >= 0);
        assert(i < xs.size());

        return { *this, i };
    }

    void update(const size_t i, std::function<T(const T&)> f)
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
};

}

#endif //SEGTREE_SEMI_SLOW_HPP
