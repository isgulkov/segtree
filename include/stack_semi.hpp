
#ifndef SEGTREE_STACK_SEMI_HPP
#define SEGTREE_STACK_SEMI_HPP

#include <vector>
#include <cassert>

#include "util/functions.hpp"

namespace seg {

template<typename T, typename Semi>
class stack_semi
{
public:
    using value_type = T;

private:
    std::vector<value_type> xs, x_sums;

public:
    size_t size() const
    {
        return xs.size();
    }

    bool empty() const
    {
        return xs.empty();
    }

    void push(const value_type& x)
    {
        xs.push_back(x);

        if(x_sums.empty()) {
            x_sums.push_back(x);
        }
        else {
            x_sums.push_back(Semi::add(x, x_sums.back()));
        }
    }

    const value_type& top() const
    {
        assert(!empty());

        return xs.back();
    }

    const value_type& min() const
    {
        assert(!empty());

        return x_sums.back();
    }

    void pop()
    {
        assert(!empty());

        xs.pop_back();
        x_sums.pop_back();
    }
};

template<typename T>
struct stack_min : stack_semi<T, fx::less<T>> { } __unused;

template<typename T>
struct stack_max : stack_semi<T, fx::greater<T>> { }  __unused;

template<typename T>
struct stack_sum : stack_semi<T, fx::addition<T>> { }  __unused;

}

#endif //SEGTREE_STACK_SEMI_HPP
