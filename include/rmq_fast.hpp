
#ifndef SEGTREE_RMQ_FAST_HPP
#define SEGTREE_RMQ_FAST_HPP

#include <vector>
#include <cassert>

#include "util/functions.hpp"
#include "util/util.hpp"

namespace seg {

template<typename T, typename Compare = fx::less<T>>
class rmq_fast
{
public:
    using index_type = size_t;
    using value_type = T;

private:
    // TODO: inherit from a specialized template type for configuration?

    std::vector<value_type> xs;
    std::vector<std::vector<index_type>> ix_min;

    template<typename InputIt>
    static std::vector<std::vector<index_type>> build_ix_min(const InputIt it_begin, const InputIt it_end)
    {
        const index_type n = it_end - it_begin;

        std::vector<std::vector<index_type>> ix_min(util::log2(n));

        for(index_type i_pow = 0; i_pow < ix_min.size(); i_pow++) {
            const index_type l_range = 2U << i_pow;

            std::vector<index_type>& row = ix_min[i_pow];

            row.resize(n - l_range + 1);

            for(index_type i_start = 0; i_start < row.size(); i_start++) {
                const index_type i_half = i_pow ? ix_min[i_pow - 1][i_start] : i_start;
                const index_type j_half = i_pow ? ix_min[i_pow - 1][i_start + l_range / 2] : i_start + 1;

                ix_min[i_pow][i_start] = Compare::apply(it_begin[i_half], it_begin[j_half]) ? i_half : j_half;
            }
        }

        return ix_min;
    }

public:
    rmq_fast() = default;

    explicit rmq_fast(const std::vector<value_type>& xs) : xs(xs), ix_min(build_ix_min(xs.cbegin(), xs.cend())) { }

    explicit rmq_fast(std::vector<value_type>&& xs) : xs(xs), ix_min(build_ix_min(xs.cbegin(), xs.cend())) { }

    template <typename InputIt>
    rmq_fast(const InputIt it_begin, const InputIt it_end) : xs(it_begin, it_end),
                                                             ix_min(build_ix_min(it_begin, it_end)) { }

    index_type size() const
    {
        return (index_type)xs.size();
    }

    bool empty() const
    {
        return xs.empty();
    }

    index_type index(const index_type i_begin, const index_type i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= xs.size());
        assert(i_begin < i_end);

        // TODO: provide some guarantee as to which of several equal indices is returned (e.g. first)

        const index_type l_range = i_end - i_begin;

        if(l_range == 1) {
            return i_begin;
        }

        const index_type i_pow = util::log2(l_range) - 1;

        if(util::is_power2(l_range)) {
            return ix_min[i_pow][i_begin];
        }

        const index_type i_min = ix_min[i_pow][i_begin];
        const index_type j_min = ix_min[i_pow][i_begin + (l_range - (2U << i_pow))];

        if(Compare::apply(xs[i_min], xs[j_min])) {
            return i_min;
        }
        else {
            return j_min;
        }
    }

    value_type get(const index_type i_begin, const index_type i_end) const
    {
        return xs[index(i_begin, i_end)];
    }
};

}

#endif //SEGTREE_RMQ_FAST_HPP
