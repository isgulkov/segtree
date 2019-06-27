
#ifndef SEGTREE_RANGE_QUERY_HPP
#define SEGTREE_RANGE_QUERY_HPP

#include <vector>
#include <functional>

/**
 * Range queries:
 * - `rmq_fast`: O(1) query, O(nlogn) space
 * - `rmq_compact`: O(logn) query, O(n) space
 * - `rmq_cartesian`: O(1) query, O(n) space
 * - `rq_group`: O(1) query, O(n) space -- for group (invertible) operators
 * - `rq_mode`: ...
 * - `rq_median`: ...
 */

namespace seg {

template<typename T, typename Compare = std::less<T>>
class rmq_fast
{
    // TODO: inherit from a specialized template type for configuration

    static inline size_t log2(size_t x)
    {
        size_t i;

        for(i = 0, x >>= 1U; x; x >>= 1U, i++) { }

        return i;
    }

    static inline bool is_power2(const size_t x)
    {
        return (x & (x - 1)) == 0;
    }

    const Compare less{ };

    const std::vector<T> xs;
    const std::vector<std::vector<size_t>> ix_min;

    static std::vector<std::vector<size_t>> build_ix_min(const std::vector<T>& xs, const Compare less = Compare())
    {
        std::vector<std::vector<size_t>> ix_min(log2(xs.size()));

        for(size_t i_pow = 0; i_pow < ix_min.size(); i_pow++) {
            const size_t l_range = 2U << i_pow;

            std::vector<size_t>& row = ix_min[i_pow];

            row.resize(xs.size() - l_range + 1);

            for(size_t i_start = 0; i_start < row.size(); i_start++) {
                const size_t i_half = i_pow ? ix_min[i_pow - 1][i_start] : i_start;
                const size_t j_half = i_pow ? ix_min[i_pow - 1][i_start + l_range / 2] : i_start + 1;

                ix_min[i_pow][i_start] = less(xs[i_half], xs[j_half]) ? i_half : j_half;
            }
        }

        return ix_min;
    }

public:
    explicit rmq_fast(const std::vector<T>& xs) : xs(xs), ix_min(build_ix_min(xs)) { }

    explicit rmq_fast(std::vector<T>&& xs) : xs(xs), ix_min(build_ix_min(xs)) { }

    size_t size() const
    {
        return xs.size();
    }

    size_t index(const size_t i_begin, const size_t i_end) const
    {
        if(i_begin < 0 || i_end > xs.size()) {
            throw std::logic_error("");
        }

        const size_t l_range = i_end - i_begin;

        if(!l_range) {
            throw std::logic_error("");
        }

        if(l_range == 1) {
            return i_begin;
        }

        const size_t i_pow = log2(l_range) - 1;

        if(is_power2(l_range)) {
            return ix_min[i_pow][i_begin];
        }

        const size_t i_min = ix_min[i_pow][i_begin];
        const size_t j_min = ix_min[i_pow][i_begin + (l_range - (2 << i_pow))];

        if(less(xs[i_min], xs[j_min])) {
            return i_min;
        }
        else {
            return j_min;
        }
    }

    T get(const size_t i_begin, const size_t i_end) const
    {
        return xs[index(i_begin, i_end)];
    }
};

}

#endif //SEGTREE_RANGE_QUERY_HPP
