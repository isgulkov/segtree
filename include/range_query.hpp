
#ifndef SEGTREE_RANGE_QUERY_HPP
#define SEGTREE_RANGE_QUERY_HPP

#include <vector>
#include <functional>

/**
 * Range queries:
 * - `rmq_fast`: O(1) query, O(nlogn) space, no update
 * - `rmq_compact`: O(logn) query, O(n) space, O(logn) single update
 * - `rmq_cartesian`: O(1) query, O(n) space
 * - `rq_group`: O(1) query, O(n) space, O(1) single update -- for group (invertible) operators
 * - `rq_mode`: ...
 * - `rq_median`: ...
 *
 * TODO: use const T& wherever possible?
 */

namespace {

inline size_t log2(size_t x)
{
    size_t i;

    for(i = 0, x >>= 1U; x; x >>= 1U, i++) { }

    return i;
}

}

namespace seg {

template<typename T, typename Compare = std::less<T>>
class rmq_fast
{
    // TODO: inherit from a specialized template type for configuration

    static inline bool is_power2(const size_t x)
    {
        return (x & (x - 1)) == 0;
    }

    const Compare less{ };

    const std::vector<T> xs;
    const std::vector<std::vector<size_t>> ix_min;

    static std::vector<std::vector<size_t>> build_ix_min(const std::vector<T>& xs, const Compare less = Compare())
    {
        std::vector<std::vector<size_t>> ix_min(log2(xs.size()));

        for(size_t i_pow = 0; i_pow < ix_min.size(); i_pow++) {
            const size_t l_range = 2U << i_pow;

            std::vector<size_t>& row = ix_min[i_pow];

            row.resize(xs.size() - l_range + 1);

            for(size_t i_start = 0; i_start < row.size(); i_start++) {
                const size_t i_half = i_pow ? ix_min[i_pow - 1][i_start] : i_start;
                const size_t j_half = i_pow ? ix_min[i_pow - 1][i_start + l_range / 2] : i_start + 1;

                ix_min[i_pow][i_start] = less(xs[i_half], xs[j_half]) ? i_half : j_half;
            }
        }

        return ix_min;
    }

public:
    explicit rmq_fast(const std::vector<T>& xs) : xs(xs), ix_min(build_ix_min(xs)) { }

    explicit rmq_fast(std::vector<T>&& xs) : xs(xs), ix_min(build_ix_min(xs)) { }

    template <typename InputIt>
    rmq_fast(InputIt it_begin, const InputIt it_end) : xs(it_begin, it_end), ix_min(build_ix_min(xs)) { }

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

        const size_t l_range = i_end - i_begin;

        if(l_range == 1) {
            return i_begin;
        }

        const size_t i_pow = log2(l_range) - 1;

        if(is_power2(l_range)) {
            return ix_min[i_pow][i_begin];
        }

        const size_t i_min = ix_min[i_pow][i_begin];
        const size_t j_min = ix_min[i_pow][i_begin + (l_range - (2U << i_pow))];

        if(less(xs[i_min], xs[j_min])) {
            return i_min;
        }
        else {
            return j_min;
        }
    }

    T get(const size_t i_begin, const size_t i_end) const
    {
        return xs[index(i_begin, i_end)];
    }
};

template<typename T, typename Compare = std::less<T>>
class rmq_compact
{
    const Compare less{ };

    const size_t n = 0;
    std::vector<T> xs_min;

    static T build_xs_min(const typename std::vector<T>::const_iterator it_begin,
                          const typename std::vector<T>::const_iterator it_end,
                          std::vector<T>& xs_min, const size_t i_node,
                          const Compare less = Compare())
    {
        if(it_begin + 1 == it_end) {
            return xs_min[i_node] = *it_begin;
        }

        const auto x_mid = it_begin + (it_end - it_begin + 1) / 2;

        const T l_min = build_xs_min(it_begin, x_mid, xs_min, (i_node + 1) * 2 - 1);
        const T r_min = build_xs_min(x_mid, it_end, xs_min, (i_node + 1) * 2);

        return xs_min[i_node] = less(l_min, r_min) ? l_min : r_min;
    }

public:
    explicit rmq_compact(const std::vector<T>& xs) : rmq_compact(xs.begin(), xs.end()) { }

    template <typename InputIt>
    rmq_compact(InputIt it_begin, const InputIt it_end) : n(it_end - it_begin),
                                                          xs_min(2 << (log2((it_end - it_begin) - 1) + 1))
    {
        // `xs_min` size is rounded up to the next power of two, where the tree would be saturated

        build_xs_min(it_begin, it_end, xs_min, 0);

        for(const T x : xs_min) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }

    size_t size() const
    {
        return n;
    }

    bool empty() const
    {
        return n == 0;
    }

private:
    T get(const size_t i_begin, const size_t i_end,
          const size_t i_left, const size_t i_right, const size_t i_node) const
    {
        if(i_begin == i_left && i_end == i_right) {
            return xs_min[i_node];
        }

        const size_t i_mid = i_left + (i_right - i_left + 1) / 2;

        if(i_end <= i_mid) {
            return get(i_begin, i_end, i_left, i_mid, (i_node + 1) * 2 - 1);
        }
        else if(i_mid <= i_begin) {
            return get(i_begin, i_end, i_mid, i_right, (i_node + 1) * 2);
        }
        else {
            const T l_min = get(i_begin, i_mid, i_left, i_mid, (i_node + 1) * 2 - 1);
            const T r_min = get(i_mid, i_end, i_mid, i_right, (i_node + 1) * 2);

            return less(l_min, r_min) ? l_min : r_min;
        }
    }

public:
    T get(const size_t i_begin, const size_t i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= n);
        assert(i_begin < i_end);

        return get(i_begin, i_end, 0, n, 0);
    }

    size_t index(const size_t i_begin, const size_t i_end) const
    {
        // This has to be doable in a DRY way
    }

private:
    void update(const size_t i, const T& x, const size_t i_left, const size_t i_right, const size_t i_node)
    {
        if(i_left == i && i_right == i + 1) {
            xs_min[i_node] = x;

            return;
        }

        const size_t i_mid = i_left + (i_right - i_left + 1) / 2;

        if(i < i_mid) {
            update(i, x, i_left, i_mid, (i_node + 1) * 2 - 1);
        }
        else {
            update(i, x, i_mid, i_right, (i_node + 1) * 2);
        }

        // TODO: use return values
        const T& l_min = xs_min[(i_node + 1) * 2 - 1];
        const T& r_min = xs_min[(i_node + 1) * 2];

        xs_min[i_node] = less(l_min, r_min) ? l_min : r_min;
    }

public:
    void set(const size_t i, const T& x)
    {
        assert(i >= 0);
        assert(i < n);

        update(i, x, 0, n, 0);
    }
};

}

#endif //SEGTREE_RANGE_QUERY_HPP
