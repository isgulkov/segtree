
#ifndef SEGTREE_RMQ_CARTESIAN_HPP
#define SEGTREE_RMQ_CARTESIAN_HPP

#include <vector>
#include <cassert>

#include <unordered_map> // TODO!: use a vector for this?

#include "rmq_fast.hpp"
#include "util/util.hpp"

namespace seg {

template<typename T, typename Compare = fx::less<T>>
class rmq_cartesian
{
public:
    using index_type = size_t;
    using value_type = T;

private:
    std::vector<value_type> xs;

    template <typename InputIt>
    static index_type compute_tree_number(const InputIt it_begin, const InputIt it_end, index_type l_block)
    {
        std::vector<value_type> xs_right;

        index_type x = 0;

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

    rmq_fast<value_type, Compare> outer_rmq;
    std::vector<rmq_fast<value_type, Compare>> inner_rmqs;

    index_type l_block = 0;

public:
    rmq_cartesian() = default;

    explicit rmq_cartesian(const std::vector<value_type>& xs) : rmq_cartesian(xs.cbegin(), xs.cend()) { }

    template <typename InputIt>
    rmq_cartesian(const InputIt it_begin, const InputIt it_end) : xs(it_begin, it_end)
    {
        const index_type n = it_end - it_begin;

        l_block = std::max(index_type(1), util::log2(n) / 4);

        std::unordered_map<index_type, index_type> ix_inner_rmqs;
        std::vector<value_type> block_mins;

        for(index_type i_b = 0; i_b <= (n - 1) / l_block; i_b++) {
            const index_type i_start = i_b * l_block;
            const index_type i_end = std::min(n, i_start + l_block);

            const index_type x_block = compute_tree_number(it_begin + i_start, it_begin + i_end, l_block);

            {
                const auto it_rmq = ix_inner_rmqs.find(x_block);

                if(it_rmq != ix_inner_rmqs.end()) {
                    inner_rmqs.emplace_back(inner_rmqs[it_rmq->second]);
                    block_mins.emplace_back(xs[i_start + inner_rmqs.back().index(0, l_block)]);

                    continue;
                }
            }

            rmq_fast<value_type, Compare> brmq(it_begin + i_start, it_begin + i_end);

            block_mins.emplace_back(xs[i_start + brmq.index(0, l_block)]);

            ix_inner_rmqs[x_block] = inner_rmqs.size();
            inner_rmqs.emplace_back(brmq);
        }

        outer_rmq = rmq_fast<value_type, Compare>(block_mins);
    }

//    explicit rmq_cartesian(std::vector<value_type>&& xs) : xs(xs) { }

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

        // TODO!: this is really NOT constant time as it should be...

        const index_type ib_first = i_begin / l_block, ib_last = (i_end - 1) / l_block;

        const index_type jb_first = i_begin - (ib_first * l_block);
        const index_type jb_last = i_end - (ib_last * l_block);

        if(ib_first == ib_last) {
            return ib_first * l_block + inner_rmqs[ib_first].index(jb_first, jb_last);
        }

        index_type i_min = ib_first * l_block + inner_rmqs[ib_first].index(jb_first, l_block);

        {
            const index_type j_min = ib_last * l_block + inner_rmqs[ib_last].index(0, jb_last);

            if(Compare::apply(xs[j_min], xs[i_min])) {
                i_min = j_min;
            }
        }

        if(ib_first + 1 == ib_last) {
            return i_min;
        }

        const index_type ib_middle = outer_rmq.index(ib_first + 1, ib_last);

        {
            const index_type j_min = ib_middle * l_block + inner_rmqs[ib_middle].index(0, l_block);

            if(Compare::apply(xs[j_min], xs[i_min])) {
                i_min = j_min;
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

#endif //SEGTREE_RMQ_CARTESIAN_HPP
