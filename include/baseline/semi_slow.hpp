
#ifndef SEGTREE_SEMI_SLOW_HPP
#define SEGTREE_SEMI_SLOW_HPP

#include <vector>
#include <cassert>

#include "functions.hpp"

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
};

}

#endif //SEGTREE_SEMI_SLOW_HPP
