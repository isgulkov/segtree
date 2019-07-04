
#ifndef SEGTREE_BENCH_UTIL_HPP
#define SEGTREE_BENCH_UTIL_HPP

#include <vector>
#include <random>

std::vector<int> random_ints(size_t n)
{
    std::mt19937 rng(std::random_device{}());
    std::binomial_distribution<int> dist(250, 0.25);

    std::vector<int> xs(n);

    for(int& x : xs) {
        x = dist(rng) - 150;
    }

    return xs;
}

#endif //SEGTREE_BENCH_UTIL_HPP
