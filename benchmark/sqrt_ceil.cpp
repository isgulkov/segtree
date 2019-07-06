#include <benchmark/benchmark.h>

#include <random>
#include <cmath>

#include "util/util.hpp"

std::vector<size_t> random_epts(size_t n)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, (1ULL < 32) - 1);

    std::vector<size_t> xs(n);

    for(size_t& x : xs) {
        x = dist(rng);
    }

    return xs;
}

void BM_SqrtCeil_Binsearch(benchmark::State& state) {
    const std::vector<size_t> xs = random_epts(state.range(0));

    for(auto _ : state) {
        for(const size_t x : xs) {
            benchmark::DoNotOptimize(seg::util::sqrt_ceil(x));
        }
    }
}

void BM_SqrtCeil_CMath(benchmark::State& state) {
    const std::vector<size_t> xs = random_epts(state.range(0));

    for(auto _ : state) {
        for(const size_t x : xs) {
            benchmark::DoNotOptimize((size_t)std::ceil(std::sqrt(x)));
        }
    }
}

BENCHMARK(BM_SqrtCeil_Binsearch)->Range(1024, 1U << 25U)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_SqrtCeil_CMath)->Range(1024, 1U << 25U)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
