
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

std::vector<std::pair<int, int>> random_segments(size_t n, const size_t size)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, size);

    std::vector<std::pair<int, int>> ps;
    ps.reserve(n);

    while(n--) {
        int a = dist(rng), b;

        do {
            b = dist(rng);
        } while(a == b);

        if(a > b) {
            std::swap(a, b);
        }

        ps.emplace_back(a, b);
    }

    return ps;
}

std::vector<std::pair<size_t, int>> random_point_vs(size_t n, const size_t size)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> i_dist(0, size - 1), x_dist(-150, 150);

    std::vector<std::pair<size_t, int>> ps;
    ps.reserve(n);

    while(n--) {
        ps.emplace_back(i_dist(rng), x_dist(rng));
    }

    return ps;
}

std::vector<std::tuple<size_t, size_t, int>> random_range_vs(size_t n, const size_t size)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> i_dist(0, size - 1), x_dist(-150, 150);

    std::vector<std::tuple<size_t, size_t, int>> ps;
    ps.reserve(n);

    while(n--) {
        size_t i = i_dist(rng), j;

        do {
            j = i_dist(rng);
        } while(i == j);

        if(i > j) {
            std::swap(i, j);
        }

        ps.emplace_back(i, j, x_dist(rng));
    }

    return ps;
}

#endif //SEGTREE_BENCH_UTIL_HPP
