
#ifndef SEGTREE_FENWICK_TREE_HPP
#define SEGTREE_FENWICK_TREE_HPP

#include <vector>
#include <cassert>
#include <functional>

namespace seg {

template<typename T, typename Add = std::plus<T>, typename Subtract = std::minus<T>>
class fenwick_tree
{
    Add _add{ };
    const Subtract _subtract{ };

    std::vector<T> xs;

public:
    fenwick_tree() = default;

    explicit fenwick_tree(const std::vector<T>& xs) : fenwick_tree(xs.cbegin(), xs.cend()) { }

    template <typename InputIt>
    fenwick_tree(const InputIt it_begin, const InputIt it_end) : xs(it_end - it_begin, 0)
    {
        for(size_t i = 0; i < xs.size(); i++) {
            add(i, it_begin[i]);
        }
    }

    size_t size() const
    {
        return xs.size();
    }

    bool empty() const
    {
        return xs.empty();
    }

private:
    T get_upto(size_t i_end) const
    {
        if(!i_end) {
            return T();
        }

        T result = xs[i_end - 1];

        while(i_end -= (i_end & -i_end)) {
            result = _add(result, xs[i_end - 1]);
        }

        return result;
    }

public:
    T get(const size_t i_begin, const size_t i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= xs.size());
        assert(i_begin < i_end);

        return _subtract(get_upto(i_end), get_upto(i_begin));
    }

    T operator[](const size_t i) const
    {
        return get(i, i + 1);
    }

    void add(const size_t i_x, const T& delta)
    {
        for(size_t j = i_x; j < xs.size(); j = j | (j + 1)) {
            xs[j] = _add(xs[j], delta);
        }
    }

    void set(const size_t i_x, const T& x)
    {
        add(i_x, _subtract(x, operator[](i_x)));
    }
};

}

#endif //SEGTREE_FENWICK_TREE_HPP
