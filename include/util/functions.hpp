
#ifndef SEGTREE_FUNCTIONS_HPP
#define SEGTREE_FUNCTIONS_HPP

#include <cmath>

namespace seg::fx {

// Orders

template<typename T = void>
struct less {
    static bool apply(const T& a, const T& b) { return a < b; }
};

template<>
struct less<void> {
    template<typename T> static bool apply(const T& a, const T& b) { return a < b; }
};

template<typename T = void>
struct greater {
    static bool apply(const T& a, const T& b) { return a > b; }
};

template<>
struct greater<void> {
    template<typename T> static bool apply(const T& a, const T& b) { return a > b; }
};

// Identity elements

template<typename T>
struct id_max {
    static constexpr T id = std::numeric_limits<T>::max();
};

template<typename T>
struct id_lowest {
    static constexpr T id = std::numeric_limits<T>::lowest();
};

// Semigroups

template<typename T, typename Compare = less<T>, typename Id = id_max<T>>
struct semi_min {
    static T add(const T& a, const T& b) { return Compare::apply(a, b) ? a : b; }
    static T multiply(const T& a, const size_t n) { return a; }
    static constexpr T id = Id::id;
};

template<typename T, typename Compare = greater<T>, typename Id = id_lowest<T>>
struct semi_max {
    static T add(const T& a, const T& b) { return Compare::apply(a, b) ? a : b; }
    static T multiply(const T& a, const size_t n) { return a; }
    static constexpr T id = Id::id;
};

// Groups

template<typename T = void>
struct addition {
    static T add(const T& a, const T& b) { return a + b; }
    static T multiply(const T& a, const size_t n) { return a * n; }
    static T subtract(const T& a, const T& b) { return a - b; }
    static constexpr T id = T();
};

template<typename T = void>
struct multiplication {
    static T add(const T& a, const T& b) { return a * b; }
    static T multiply(T a, size_t n) { return std::pow(a, n); }
    static T subtract(const T& a, const T& b) { return a / b; }
    static constexpr T id = T(1);
};

// TODO: is there a way to have a usable id() for the specialization below?

//template<>
//struct addition<void> {
//    template<typename T> static T add(const T& a, const T& b) { return a + b; }
//    template<typename T> static T subtract(const T& a, const T& b) { return a - b; }
//    template<typename T> static T id() { return T(); }
//};

}

#endif //SEGTREE_FUNCTIONS_HPP
