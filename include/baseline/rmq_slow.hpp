
#ifndef SEGTREE_RMQ_SLOW_HPP
#define SEGTREE_RMQ_SLOW_HPP

#include <vector>
#include <cassert>
#include <functional>

namespace seg::baseline {

template<typename T, typename Compare = std::less<T>>
class rmq_slow
{
    // TODO: inherit from a specialized template type for configuration

    const Compare less{ };

    const std::vector<T> xs;

public:
    explicit rmq_slow(const std::vector<T>& xs) : xs(xs) { }

    explicit rmq_slow(std::vector<T>&& xs) : xs(xs) { }

    template <typename InputIt>
    rmq_slow(InputIt it_begin, const InputIt it_end) : xs(it_begin, it_end) { }

    size_t size() const
    {
        return xs.size();
    }

    size_t index(const size_t i_begin, const size_t i_end) const
    {
        assert(0 <= i_begin);
        assert(i_end <= xs.size());
        assert(i_begin < i_end);

        size_t i_min = i_begin;

        for(size_t i = i_begin + 1; i < i_end; i++) {
            if(less(xs[i], xs[i_min])) {
                i_min = i;
            }
        }

        return i_min;
    }

    T get(const size_t i_begin, const size_t i_end) const
    {
        return xs[index(i_begin, i_end)];
    }
};

}

#endif //SEGTREE_RMQ_SLOW_HPP
