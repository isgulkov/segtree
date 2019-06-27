
#ifndef SEGTREE_UTIL_HPP
#define SEGTREE_UTIL_HPP

namespace seg::util {

inline size_t log2(size_t x)
{
    size_t i;

    for(i = 0, x >>= 1U; x; x >>= 1U, i++) { }

    return i;
}

inline bool is_power2(const size_t x)
{
    return (x & (x - 1)) == 0;
}

}

#endif //SEGTREE_UTIL_HPP
