
#ifndef SEGTREE_RQ_GROUP_HPP
#define SEGTREE_RQ_GROUP_HPP

#include <vector>
#include <cassert>
#include <functional>

namespace seg {

template<typename T, typename Add = std::plus<T>, typename Subtract = std::minus<T>>
class rq_group
{
    // TODO: check that no runtime overhead is incurred by this generalisation over simple int sum

    const Add add{ };
    const Subtract subtract{ };

    const std::vector<T> vs;

    template <typename InputIt>
    static std::vector<T> build_prefix_vs(InputIt it_begin, const InputIt it_end, const Add add = Add())
    {
        if(it_begin == it_end) {
            return {};
        }

        std::vector<T> vs;
        vs.reserve(it_end - it_begin);

        vs.emplace_back(*it_begin++);

        while(it_begin != it_end) {
            vs.emplace_back(add(vs.back(), *it_begin++));
        }

        return vs;
    }

    static std::vector<T> build_prefix_vs(std::vector<T>&& xs, const Add add = Add())
    {
        // TODO: std::move doesn't have any effect here, right?
        auto vs = std::move(xs);

        for(size_t i = 1; i < vs.size(); i++) {
            vs[i] = add(vs[i], vs[i - 1]);
        }

        return vs;
    }

public:
    explicit rq_group(const std::vector<T>& xs) : rq_group(xs.begin(), xs.end()) { }

    template <typename InputIt>
    rq_group(InputIt it_begin, const InputIt it_end) : vs(build_prefix_vs(it_begin, it_end)) { }

    explicit rq_group(std::vector<T>&& xs) : vs(build_prefix_vs(xs)) { }

    size_t size() const
    {
        return vs.size();
    }

    T get(const size_t i_begin, const size_t i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= vs.size());

        if(i_begin >= i_end) {
            return T();
        }

        if(i_begin) {
            return subtract(vs[i_end - 1], vs[i_begin - 1]);
        }
        else {
            return vs[i_end - 1];
        }
    }
};

}

#endif //SEGTREE_RQ_GROUP_HPP
