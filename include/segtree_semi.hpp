
#ifndef SEGTREE_SEGTREE_SEMI_HPP
#define SEGTREE_SEGTREE_SEMI_HPP

#include <vector>
#include <cassert>

#include "util/functions.hpp"
#include "util/util.hpp"
#include "util/elem_handle.hpp"

namespace seg {

template<typename T, typename Semi>
class segtree_semi
{
    // TODO: visibility annotations? (https://libcxx.llvm.org/docs/DesignDocs/VisibilityMacros.html)

public:
    using index_type = size_t;
    using value_type = T;

private:
    index_type n = 0;
    std::vector<value_type> xs_nodes;

public:
    segtree_semi() = default;

//    TODO: use this?
//    std::vector<value_type>&& xs

    explicit segtree_semi(const std::vector<value_type>& xs) : segtree_semi(xs.cbegin(), xs.cend()) { }

    template <typename InputIt>
    segtree_semi(InputIt it_begin, const InputIt it_end) : n(it_end - it_begin),
                                                                xs_nodes(2 << (util::log2(n - 1) + 1), Semi::id())
    {
        // `xs_min` size is rounded up to the next power of two, where the tree would be saturated
        // TODO!: only make it as large as necessary
        // TODO!: initialization with id() seems to be unnecessary

        // TODO: make `xs_nodes` 0-based, perhaps extract some of the index work, comment the traversals

        for(index_type i = 0; i < n; i++) {
            xs_nodes[n + i] = *it_begin++;
        }

        for(index_type i = n - 1; i != 0; i--) {
            xs_nodes[i] = Semi::add(xs_nodes[2 * i], xs_nodes[2 * i + 1]);
        }
    }

    index_type size() const
    {
        return n;
    }

    bool empty() const
    {
        return n == 0;
    }

    value_type get(const index_type i_begin, const index_type i_end) const
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

        value_type result = Semi::id();

        for(index_type l = i_begin + n, r = i_end + n; l < r; l /= 2, r /= 2) {
            /**
             * For each node, one of two options if chosen:
             *   - if the parent is completely within/outside segment, proceed to it;
             *   - otherwise, proceed to the parent's inner sibling, after adding node's contribution to `result`.
             *
             * Due to how the tree is built, indices of left children are odd, of right children -- even.
             *
             * TODO: Adapt for the non-commutative case (add everything left-to-right)
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

    value_type operator[](const index_type i) const {
        assert(i >= 0);
        assert(i < n);

        // TODO: just return const& to `xs_nodes[n + i]` in the non-lazy version (which is what this is)

        return get(i, i + 1);
    }

    void set(index_type i, const value_type& x)
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

    util::elem_handle<segtree_semi> operator[](const index_type i)
    {
        assert(i >= 0);
        assert(i < n);

        return { *this, i };
    }
};

template<typename T>
using segtree_sum = segtree_semi<T, fx::addition<T>>;

template<typename T>
using segtree_min = segtree_semi<T, fx::semi_min<T>>;

template<typename T>
using segtree_max = segtree_semi<T, fx::semi_max<T>>;

}

#endif //SEGTREE_SEGTREE_SEMI_HPP
