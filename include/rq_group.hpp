
#ifndef SEGTREE_RQ_GROUP_HPP
#define SEGTREE_RQ_GROUP_HPP

#include <vector>
#include <cassert>

#include "util/functions.hpp"

namespace seg {

template<typename T, typename Group = fx::addition<T>>
class rq_group
{
public:
    using index_type = size_t;
    using value_type = T;

private:
    const std::vector<value_type> vs;

    template <typename InputIt>
    static std::vector<value_type> build_prefix_vs(InputIt it_begin, const InputIt it_end)
    {
        if(it_begin == it_end) {
            return {};
        }

        std::vector<value_type> vs;
        vs.reserve(it_end - it_begin);

        vs.emplace_back(*it_begin++);

        while(it_begin != it_end) {
            vs.emplace_back(Group::add(vs.back(), *it_begin++));
        }

        return vs;
    }

    static std::vector<value_type> build_prefix_vs(std::vector<value_type>&& xs)
    {
        // TODO: std::move doesn't have any effect here, right?
        auto vs = std::move(xs);

        for(index_type i = 1; i < vs.size(); i++) {
            vs[i] = Group::add(vs[i], vs[i - 1]);
        }

        return vs;
    }

public:
    rq_group() = default;

    explicit rq_group(const std::vector<value_type>& xs) : rq_group(xs.begin(), xs.end()) { }

    template <typename InputIt>
    rq_group(InputIt it_begin, const InputIt it_end) : vs(build_prefix_vs(it_begin, it_end)) { }

    explicit __attribute__((unused)) rq_group(std::vector<value_type>&& xs) : vs(build_prefix_vs(xs)) { }

    index_type size() const
    {
        return (index_type)vs.size();
    }

    bool empty() const
    {
        return vs.empty();
    }

    value_type get(const index_type i_begin, const index_type i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= vs.size());
        assert(i_begin < i_end);

        if(i_begin) {
            return Group::subtract(vs[i_end - 1], vs[i_begin - 1]);
        }
        else {
            return vs[i_end - 1];
        }
    }
};

}

#endif //SEGTREE_RQ_GROUP_HPP
