
#ifndef SEGTREE_RQ_MODE_COMPACT_HPP
#define SEGTREE_RQ_MODE_COMPACT_HPP

#include <vector>
#include <cassert>
#include <optional>

#include <unordered_map>

#include <iostream> // TODO!: <- REMOVE

#include "util/util.hpp"

namespace seg {

template<typename T>
class rq_mode_compact
{
    std::vector<T> xs_unique;
    std::vector<size_t> ix_unique;
    std::vector<size_t> ix_occur;

    std::vector<std::vector<size_t>> ix_occur_each;

    size_t l_block, n_blocks;

    std::vector<std::vector<std::pair<size_t, size_t>>> mx_block;

public:
    rq_mode_compact() = default;

//    explicit rq_mode_compact(std::vector<T>&& xs) : xs(xs) { }
    explicit rq_mode_compact(const std::vector<T>& xs) : rq_mode_compact(xs.begin(), xs.end()) { }

    template<typename InputIt>
    rq_mode_compact(const InputIt it_begin, const InputIt it_end)
    {
        const size_t n = it_end - it_begin;

        l_block = util::sqrt_ceil(n);
        n_blocks = n / l_block + (n % l_block != 0);

//        std::cout << l_block << " " << n_blocks << std::endl;

        ix_unique.reserve(n);

        std::unordered_map<T, size_t> ix_occ;

        for(InputIt it = it_begin; it != it_end; it++) {
            size_t i_occ;

            {
                const auto it_occ = ix_occ.find(*it);

                if(it_occ != ix_occ.end()) {
                    i_occ = it_occ->second;
                }
                else {
                    xs_unique.emplace_back(*it);
                    i_occ = (ix_occ[*it] = ix_occ.size());
                }
            }

            ix_unique.push_back(i_occ);
        }

//        for(const size_t r : ranks) {
//            std::cout << r << " ";
//        }
//        std::cout << std::endl;

        ix_occur.reserve(n);
        ix_occur_each.resize(ix_occ.size());

        for(size_t i = 0; i < n; i++) {
            const size_t i_occ = ix_occ[it_begin[i]];

            std::vector<size_t>& ix_occur_v = ix_occur_each[i_occ];

            ix_occur.push_back(ix_occur_v.size());
            ix_occur_v.push_back(i);
        }

//        for(const std::vector<size_t>& ps : qs) {
//            for(const size_t p : ps) {
//                std::cout << p << " ";
//            }
//            std::cout << std::endl;
//        }
//        std::cout << std::endl;

//        for(const size_t r : b_prime) {
//            std::cout << r << " ";
//        }
//        std::cout << std::endl;
//
//        std::cout << std::endl;

        mx_block.resize(n_blocks);

        for(size_t ib_begin = 0; ib_begin < n_blocks; ib_begin++) {
            auto& mx_block_row = mx_block[ib_begin];

            mx_block_row.reserve(n_blocks - ib_begin);

            size_t i_max = SIZE_T_MAX, n_max = 0;

            std::unordered_map<size_t, size_t> counts;

            for(size_t lb = 0; lb < n_blocks - ib_begin; lb++) {
                const size_t i_block_end = std::min(n, (ib_begin + lb + 1) * l_block);

                for(size_t i = (ib_begin + lb) * l_block; i < i_block_end; i++) {
                    const size_t v_count = ++counts[ix_unique[i]];

                    if(v_count > n_max) {
                        n_max = v_count;
                        i_max = ix_unique[i];
                    }
                    else if(v_count == n_max) {
                        i_max = SIZE_T_MAX;
                    }
                }

                mx_block_row.emplace_back(i_max, n_max);
            }
        }

//        for(size_t i = 0; i < n_blocks; i++) {
//            for(size_t l = 0; l < n_blocks - i; l++) {
//                std::cout << xs_unique[s_mode[i][l]] << "(" << s_freq[i][l] << ") ";
//            }
//            std::cout << std::endl;
//        }
//        std::cout << std::endl;

        // ...
    }

    size_t size() const
    {
        return ix_occur.size();
    }

    bool empty() const {
        return ix_occur.empty();
    }

private:
    void _update_mode(const size_t i, const size_t i_begin, const size_t i_end, size_t& i_max, size_t& c_max) const
    {
        const size_t i_v = ix_unique[i];

        if(i_v == i_max) {
            return;
        }

        const std::vector<size_t>& ix_occur_v = ix_occur_each[i_v];

        const size_t i_occur = ix_occur[i];

        // TODO!: these are actually necessary
//        if(i_occur && ix_occur_v[i_occur - 1] >= i_begin) {
//            return;
//        }

//        if(c_max != 0 && (i_occur + c_max >= ix_occur_v.size() || ix_occur_v[i_occur + c_max] >= i_end)) {
//            continue;
//        }

        const size_t c = std::lower_bound(ix_occur_v.cbegin(), ix_occur_v.cend(), i_end) - std::lower_bound(ix_occur_v.cbegin(), ix_occur_v.cend(), i_begin);

        if(c > c_max) {
            i_max = i_v;
            c_max = c;
        }
        else if(c == c_max) {
            i_max = SIZE_T_MAX;
        }
    }

public:
    std::optional<T> get(const size_t i_begin, const size_t i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= ix_unique.size());
        assert(i_begin < i_end);

        // TODO: improve both readability and performance

        // First block completely contained
        const size_t ib_begin = i_begin / l_block + (i_begin % l_block != 0);

        // The block after last one completely contained
        const size_t ib_end = i_end != ix_occur.size() ? i_end / l_block : n_blocks;

        size_t i_max = SIZE_T_MAX, c_max = 0;

        if(ib_begin < ib_end) {
            const auto& p_mode = mx_block[ib_begin][ib_end - ib_begin - 1];

            i_max = p_mode.first;
            c_max = p_mode.second;
        }

        size_t i_prefix_end = std::min(i_end, ib_begin * l_block);
        size_t i_suffix_begin = std::max(i_begin, std::min(ix_occur.size(), ib_end * l_block));

        if(i_suffix_begin < i_prefix_end) {
            i_suffix_begin = i_prefix_end;
        }

        if(i_max != SIZE_T_MAX) {
            for(size_t i = i_begin; i < i_prefix_end; i++) {
                if(ix_unique[i] == i_max) {
                    c_max += 1;
                }
            }

            for(size_t i = i_suffix_begin; i < i_end; i++) {
                if(ix_unique[i] == i_max) {
                    c_max += 1;
                }
            }
        }

        {
            for(size_t i = i_begin; i < i_prefix_end; i++) {
                _update_mode(i, i_begin, i_end, i_max, c_max);
            }

            for(size_t i = i_suffix_begin; i < i_end; i++) {
                _update_mode(i, i_begin, i_end, i_max, c_max);
            }
        }

        if(i_max == SIZE_T_MAX) {
            return std::nullopt;
        }

        return xs_unique[i_max];
    }
};

}

#endif //SEGTREE_RQ_MODE_COMPACT_HPP
