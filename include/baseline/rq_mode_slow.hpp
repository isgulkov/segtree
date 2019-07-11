
#ifndef SEGTREE_RQ_MODE_SLOW_HPP
#define SEGTREE_RQ_MODE_SLOW_HPP

#include <vector>
#include <cassert>
#include <optional>

#include <unordered_map>

namespace seg::baseline {

/**
 * This uses the counting method: O(n) space, O(j - i) query
 */
template<typename T>
class rq_mode_slow
{
public:
    using index_type = size_t;
    using value_type = T;

private:
    std::vector<value_type> xs;

public:
    rq_mode_slow() = default;

    explicit rq_mode_slow(std::vector<value_type>&& xs) : xs(xs) { }
    explicit rq_mode_slow(const std::vector<value_type>& xs) : xs(xs) { }

    template<typename InputIt>
    rq_mode_slow(const InputIt it_begin, const InputIt it_end) : xs(it_begin, it_end) { }

    index_type size() const
    {
        return (index_type)xs.size();
    }

    bool empty() const {
        return xs.empty();
    }

    /**
     * Returns {@code std::nullopt} if no unique mode exists
     *
     * TODO: another method that returns one of the values
     */
    std::optional<value_type> get(const index_type i_begin, const index_type i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= xs.size());
        assert(i_begin < i_end);

        std::unordered_map<value_type, index_type> counts;

        bool is_unique = false;
        value_type v_max;

        for(index_type n_max = 0, i = i_begin; i != i_end; i++) {
            const value_type& v = xs[i];

            // For a non-existent key, [] initializes the value with _Tp(), which (for integers) is zero
            const index_type n = ++counts[v];

            if(n > n_max) {
                is_unique = true;

                v_max = v;
                n_max = n;
            }
            else if(n == n_max) {
                is_unique = false;
            }
        }

        if(!is_unique) {
            return std::nullopt;
        }

        return v_max;
    }
};

}

#endif //SEGTREE_RQ_MODE_SLOW_HPP
