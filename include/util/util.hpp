
#ifndef SEGTREE_UTIL_HPP
#define SEGTREE_UTIL_HPP

#include <type_traits>
#include <cassert>

namespace seg::util {

template<typename Int, typename = std::enable_if_t<std::is_integral_v<Int>>>
inline Int log2(Int x)
{
    assert(x >= 0);

    Int i;

    for(i = 0, x >>= 1U; x; x >>= 1U, i++) { }

    return i;
}

template<typename Int, typename = std::enable_if_t<std::is_integral_v<Int>>>
inline bool is_power2(const Int x)
{
    assert(x >= 0);

    return (x & (x - 1)) == 0;
}

template<typename Int, typename = std::enable_if_t<std::is_integral_v<Int>>>
Int sqrt_ceil(const Int x)
{
    assert(x >= 0);

    size_t l = 0, r = std::min(x, Int(1) << (sizeof(Int) * 4));

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
