
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
    std::vector<std::vector<std::optional<T>>> modes;

public:
    rq_mode_fast() = default;

//    explicit rq_mode_fast(std::vector<T>&& xs) : xs(xs) { }
    explicit rq_mode_fast(const std::vector<T>& xs) : rq_mode_fast(xs.cbegin(), xs.cend()) { }

    template<typename InputIt>
    rq_mode_fast(const InputIt it_begin, const InputIt it_end)
    {
        modes.reserve(it_end - it_begin);

        for(InputIt it_start = it_begin; it_start != it_end; it_start++) {
            bool is_unique = false;
            size_t c_mode = 0;
            T v_mode;

            modes.emplace_back();

            std::unordered_map<T, size_t> counts;

            for(InputIt it = it_start; it != it_end; it++) {
                const size_t c = ++counts[*it];

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

    size_t size() const
    {
        return modes.size();
    }

    bool empty() const {
        return modes.empty();
    }

    /**
     * Returns {@code std::nullopt} if no unique mode exists
     *
     * TODO: another method that returns one of the values
     */
    std::optional<T> get(const size_t i_begin, const size_t i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= modes.size());
        assert(i_begin < i_end);

        return modes[i_begin][i_end - i_begin - 1];
    }
};

}

#endif //SEGTREE_RQ_MODE_FAST_HPP
