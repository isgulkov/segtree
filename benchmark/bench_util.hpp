
#ifndef SEGTREE_BENCH_UTIL_HPP
#define SEGTREE_BENCH_UTIL_HPP

#include <vector>
#include <random>

std::vector<int> random_ints_bin(size_t n, const int t = 250)
{
    std::mt19937 rng(std::random_device{}());
    std::binomial_distribution<int> dist(t, 0.25);

    std::vector<int> xs(n);

    for(int& x : xs) {
        x = dist(rng) - t / 2;
    }

    return xs;
}

std::vector<int> random_ints_few(size_t n)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, std::max(1UL, n / 2));

    std::vector<int> xs(n);

    for(int& x : xs) {
        x = dist(rng);
    }

    return xs;
}

#endif //SEGTREE_BENCH_UTIL_HPP
