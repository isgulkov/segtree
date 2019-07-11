
#ifndef SEGTREE_RQ_MODE_FAST_HPP
#define SEGTREE_RQ_MODE_FAST_HPP

#include <vector>
#include <cassert>
#include <optional>

#include <unordered_map>

namespace seg {

/**
 * This uses the counting method: O(n) space, O(j - i) query
 */
template<typename T>
class rq_mode_fast
{
public:
    using index_type = size_t;
    using value_type = T;

private:
    std::vector<std::vector<std::optional<value_type>>> modes;

public:
    rq_mode_fast() = default;

//    explicit rq_mode_fast(std::vector<value_type>&& xs) : xs(xs) { }
    explicit rq_mode_fast(const std::vector<value_type>& xs) : rq_mode_fast(xs.cbegin(), xs.cend()) { }

    template<typename InputIt>
    rq_mode_fast(const InputIt it_begin, const InputIt it_end)
    {
        modes.reserve(it_end - it_begin);

        for(InputIt it_start = it_begin; it_start != it_end; it_start++) {
            bool is_unique = false;
            index_type c_mode = 0;
            value_type v_mode;

            modes.emplace_back();

            std::unordered_map<value_type, index_type> counts;

            for(InputIt it = it_start; it != it_end; it++) {
                const index_type c = ++counts[*it];

                if(c > c_mode) {
                    c_mode = c;
                    v_mode = *it;
                    is_unique = true;
                }
                else if(c == c_mode) {
                    is_unique = false;
                }

                if(is_unique) {
                    modes.back().emplace_back(v_mode);
                }
                else {
                    modes.back().emplace_back(std::nullopt);
                }
            }
        }
    }

    index_type size() const
    {
        return (index_type)modes.size();
    }

    bool empty() const {
        return modes.empty();
    }

    /**
     * Returns {@code std::nullopt} if no unique mode exists
     *
     * TODO: another method that returns one of the values
     */
    std::optional<value_type> get(const index_type i_begin, const index_type i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= modes.size());
        assert(i_begin < i_end);

        return modes[i_begin][i_end - i_begin - 1];
    }
};

}

#endif //SEGTREE_RQ_MODE_FAST_HPP
