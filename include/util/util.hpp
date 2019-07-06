
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

size_t sqrt_ceil(const size_t x)
{
    size_t l = 0, r = std::min(x, 1UL << (sizeof(size_t) * 4));

    while(l < r) {
        const size_t m = l + (r - l) / 2;

        if(m * m < x) {
            l = m + 1;
        }
        else {
            r = m;
        }
    }

    return l;
}

}

#endif //SEGTREE_UTIL_HPP
