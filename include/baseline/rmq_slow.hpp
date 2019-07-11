
#ifndef SEGTREE_RMQ_SLOW_HPP
#define SEGTREE_RMQ_SLOW_HPP

#include <vector>
#include <cassert>

#include "util/functions.hpp"

namespace seg::baseline {

template<typename T, typename Compare = fx::less<T>>
class rmq_slow
{
public:
    using index_type = size_t;
    using value_type = T;

private:
    const std::vector<value_type> xs;

public:
    explicit rmq_slow(const std::vector<value_type>& xs) : xs(xs) { }

    explicit rmq_slow(std::vector<value_type>&& xs) : xs(xs) { }

    template <typename InputIt>
    rmq_slow(InputIt it_begin, const InputIt it_end) : xs(it_begin, it_end) { }

    index_type size() const
    {
        return (index_type)xs.size();
    }

    index_type index(const index_type i_begin, const index_type i_end) const
    {
        assert(0 <= i_begin);
        assert(i_end <= xs.size());
        assert(i_begin < i_end);

        index_type i_min = i_begin;

        for(index_type i = i_begin + 1; i < i_end; i++) {
            if(Compare::apply(xs[i], xs[i_min])) {
                i_min = i;
            }
        }

        return i_min;
    }

    value_type get(const index_type i_begin, const index_type i_end) const
    {
        return xs[index(i_begin, i_end)];
    }
};

}

#endif //SEGTREE_RMQ_SLOW_HPP
