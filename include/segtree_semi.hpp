
#ifndef SEGTREE_SEGTREE_SEMI_HPP
#define SEGTREE_SEGTREE_SEMI_HPP

#include <vector>
#include <cassert>

#include "util/functions.hpp"
#include "util/util.hpp"

namespace seg {

template<typename T, typename Semi = fx::addition<T>>
class segtree_semi
{
    size_t n = 0;
    std::vector<T> xs_nodes;

public:
    segtree_semi() = default;

//    TODO: use this?
//    std::vector<T>&& xs

    explicit segtree_semi(const std::vector<T>& xs) : segtree_semi(xs.cbegin(), xs.cend()) { }

    template <typename InputIt>
    segtree_semi(InputIt it_begin, const InputIt it_end) : n(it_end - it_begin),
                                                                xs_nodes(2 << (util::log2(n - 1) + 1), Semi::id())
    {
        // `xs_min` size is rounded up to the next power of two, where the tree would be saturated
        // TODO!: only make it as large as necessary
        // TODO!: initialization with id() seems to be unnecessary

        // TODO: make `xs_nodes` 0-based, perhaps extract some of the index work, comment the traversals

        for(size_t i = 0; i < n; i++) {
            xs_nodes[n + i] = *it_begin++;
        }

        for(size_t i = n - 1; i != 0; i--) {
            xs_nodes[i] = Semi::add(xs_nodes[2 * i], xs_nodes[2 * i + 1]);
        }
    }

    size_t size() const
    {
        return n;
    }

    bool empty() const
    {
        return n == 0;
    }

    T get(const size_t i_begin, const size_t i_end) const
    {
        assert(i_begin >= 0);
        assert(i_end <= n);
        assert(i_begin < i_end);

        /**
         * This non-recursive implementation of segtree query is ~3–5 times faster for me, so the index-fucking involved
         * is worth it. More info:
         *   - https://codeforces.com/blog/entry/1256
         *   - https://codeforces.com/blog/entry/18051
         */

        /**
         * The tree traversal starts from `i_begin`, `i_end` single-element leaves, goes up the tree towards a final
         * common ancestor, processing partial contributions from fully-included nodes.
         */

        T result = Semi::id();

        for(size_t l = i_begin + n, r = i_end + n; l < r; l /= 2, r /= 2) {
            /**
             * For each node, one of two options if chosen:
             *   - if the parent is completely within/outside segment, proceed to it;
             *   - otherwise, proceed to the parent's inner sibling, after adding node's contribution to `result`.
             *
             * Due to how the tree is built, indices of left children are odd, of right children -- even.
             */

            if(l % 2) {
                /**
                 * `l` is a right child, so its parent isn't fully included in the segment.
                 */

                result = Semi::add(result, xs_nodes[l++]);
            }

            if(r % 2) {
                /**
                 * `r` is a right child, so its parent isn't fully outside the segment.
                 */

                result = Semi::add(result, xs_nodes[--r]);
            }
        }

        return result;
    }

    void set(size_t i, const T& x)
    {
        assert(i >= 0);
        assert(i < n);

        /**
         * Ascend from `i`th single element leaf (index `i + n`) up to the root, updating values
         */

        for(xs_nodes[i += n] = x; i > 1; i /= 2) {
            /**
             * Use values of the node and its sibling to update their parent
             */

            xs_nodes[i / 2] = Semi::add(xs_nodes[i], xs_nodes[i ^ 1U]);
        }
    }
};

template<typename T>
struct segtree_min : segtree_semi<T, fx::semi_min<T>>
{
    using segtree_semi<T, fx::semi_min<T>>::segtree_semi;
};

template<typename T>
struct segtree_max : segtree_semi<T, fx::semi_max<T>>
{
    using segtree_semi<T, fx::semi_max<T>>::segtree_semi;
};

}

#endif //SEGTREE_SEGTREE_SEMI_HPP
