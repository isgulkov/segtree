
#ifndef SEGTREE_SEGTREE_SLOW_HPP
#define SEGTREE_SEGTREE_SLOW_HPP

#include <vector>
#include <cassert>
#include <numeric>

namespace seg::baseline {

template<typename T>
class segtree_slow
{
    std::vector<T> xs;

public:
    segtree_slow() = default;

    explicit segtree_slow(const std::vector<T>& xs) : xs(xs) { }

    template <typename InputIt>
    segtree_slow(const InputIt it_begin, const InputIt it_end) : xs(it_begin, it_end) { }

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

        return std::accumulate(xs.begin() + i_begin, xs.begin() + i_end, T());
    }

    void set(const size_t i, const T& x)
    {
        assert(i >= 0);
        assert(i < xs.size());

        xs[i] = x;
    }
};

}

#endif //SEGTREE_SEGTREE_SLOW_HPP
