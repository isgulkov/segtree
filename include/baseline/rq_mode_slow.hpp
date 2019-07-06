
#ifndef SEGTREE_RQ_MODE_SLOW_HPP
#define SEGTREE_RQ_MODE_SLOW_HPP

#include <vector>
#include <cassert>

#include <unordered_map>

namespace seg::baseline {

/**
 * This uses the counting method: O(n) space, O(j - i) query
 */
template<typename T>
class rq_mode_slow
{
    std::vector<T> xs;

public:
    rq_mode_slow() = default;

    explicit rq_mode_slow(std::vector<T>&& xs) : xs(xs) { }
    explicit rq_mode_slow(const std::vector<T>& xs) : xs(xs) { }

    template<typename InputIt>
    rq_mode_slow(const InputIt it_begin, const InputIt it_end) : xs(it_begin, it_end) { }

    size_t size() const
    {
        return xs.size();
    }

    bool empty() const {
        return xs.empty();
    }

    T get(const size_t i_begin, const size_t i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= xs.size());
        assert(i_begin < i_end);

        std::unordered_map<T, size_t> counts;

        // If several identical modes exist, return the smallest one
        T v_max;

        for(size_t n_max = 0, i = i_begin; i != i_end; i++) {
            const T& v = xs[i];

            // For a non-existent key, [] initializes the value with _Tp(), which (for integers) is zero
            const size_t n = ++counts[v];

            if(n > n_max) {
                v_max = v;
                n_max = n;
            }
            else if(n == n_max && v < v_max) {
                v_max = v;
            }
        }

        return v_max;
    }
};

}

#endif //SEGTREE_RQ_MODE_SLOW_HPP
