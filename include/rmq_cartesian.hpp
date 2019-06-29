
#ifndef SEGTREE_RMQ_CARTESIAN_HPP
#define SEGTREE_RMQ_CARTESIAN_HPP

#include <vector>
#include <cassert>
#include <functional>

#include <unordered_map> // TODO!: use a vector for this?

#include "rmq_fast.hpp"
#include "util.hpp"

namespace seg {

template<typename T, typename Compare = std::less<T>>
class rmq_cartesian
{
    Compare less{ };

    std::vector<T> xs;

    template <typename InputIt>
    static size_t compute_tree_number(const InputIt it_begin, const InputIt it_end, size_t l_block)
    {
        std::vector<T> xs_right;

        size_t x = 0;

        for(auto it = it_begin; it != it_end; it++, l_block--) {
            while(!xs_right.empty() && xs_right.back() >= *it) {
                xs_right.pop_back();

                x <<= 1U;
            }

            xs_right.emplace_back(*it);

            x = (x << 1U) | 1U;
        }

        x <<= l_block;
        x |= (1U << l_block) - 1;

        return x;
    }

    rmq_fast<T, Compare> outer_rmq;
    std::vector<rmq_fast<T, Compare>> inner_rmqs;

    size_t l_block;

public:
    rmq_cartesian() = default;

    explicit rmq_cartesian(const std::vector<T>& xs) : rmq_cartesian(xs.begin(), xs.end()) { }

    template <typename InputIt>
    rmq_cartesian(const InputIt it_begin, const InputIt it_end) : xs(it_begin, it_end)
    {
        const size_t n = it_end - it_begin;
        l_block = std::max(size_t(1), util::log2(n) / 4);

        std::unordered_map<size_t, size_t> ix_inner_rmqs;

        std::vector<T> block_mins;

        for(size_t i_b = 0; i_b <= (n - 1) / l_block; i_b++) {
            const size_t i_start = i_b * l_block;
            const size_t i_end = std::min(n, i_start + l_block);

            const size_t x_block = compute_tree_number(it_begin + i_start, it_begin + i_end, l_block);

            {
                const auto it_rmq = ix_inner_rmqs.find(x_block);

                if(it_rmq != ix_inner_rmqs.end()) {
                    inner_rmqs.emplace_back(inner_rmqs[it_rmq->second]);
                    block_mins.emplace_back(xs[i_start + inner_rmqs.back().index(0, l_block)]);

                    continue;
                }
            }

            rmq_fast<T, Compare> brmq(it_begin + i_start, it_begin + i_end);

            block_mins.emplace_back(xs[i_start + brmq.index(0, l_block)]);

            ix_inner_rmqs[x_block] = inner_rmqs.size();
            inner_rmqs.emplace_back(brmq);
        }

        outer_rmq = rmq_fast<T, Compare>(block_mins);
    }

//    explicit rmq_cartesian(std::vector<T>&& xs) : xs(xs) { }

    size_t size() const
    {
        return xs.size();
    }

    bool empty() const
    {
        return xs.empty();
    }

    size_t index(const size_t i_begin, const size_t i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= xs.size());
        assert(i_begin < i_end);

        const size_t ib_first = i_begin / l_block, ib_last = (i_end - 1) / l_block;

        const size_t jb_first = i_begin - (ib_first * l_block);
        const size_t jb_last = i_end - (ib_last * l_block);

        if(ib_first == ib_last) {
            return ib_first * l_block + inner_rmqs[ib_first].index(jb_first, jb_last);
        }

        size_t i_min = ib_first * l_block + inner_rmqs[ib_first].index(jb_first, l_block);

        {
            const size_t j_min = ib_last * l_block + inner_rmqs[ib_last].index(0, jb_last);

            if(less(xs[j_min], xs[i_min])) {
                i_min = j_min;
            }
        }

        if(ib_first + 1 == ib_last) {
            return i_min;
        }

        const size_t ib_middle = outer_rmq.index(ib_first + 1, ib_last);

        {
            const size_t j_min = ib_middle * l_block + inner_rmqs[ib_middle].index(0, l_block);

            if(less(xs[j_min], xs[i_min])) {
                i_min = j_min;
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

#endif //SEGTREE_RMQ_CARTESIAN_HPP
