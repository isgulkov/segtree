#include <random>

#include <benchmark/benchmark.h>

#include "baseline/rmq_slow.hpp"
#include "rmq_fast.hpp"
#include "rmq_compact.hpp"
#include "rmq_cartesian.hpp"

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

template<typename RMQ>
void BM_RMQ_RandomCreate(benchmark::State& state) {
    std::vector<int> xs = random_ints(state.range(0));

    for(auto _ : state) {
        RMQ rmq(xs);

        benchmark::DoNotOptimize(rmq.get(0, 1));
    }
}

template<typename RMQ>
void BM_RMQ_RandomAll(benchmark::State& state) {
    std::vector<int> xs = random_ints(state.range(0));

    RMQ rmq(xs);

    for(auto _ : state) {
        for(int i = 0; i < xs.size(); i++) {
            for(int j = i + 1; j < xs.size(); j++) {
                benchmark::DoNotOptimize(rmq.get(i, j));
            }
        }
    }
}

BENCHMARK_TEMPLATE(BM_RMQ_RandomCreate, seg::baseline::rmq_slow<int>)->Range(1024, 256 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomCreate, seg::rmq_compact<int>)->Range(1024, 256 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomCreate, seg::rmq_fast<int>)->Range(1024, 256 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomCreate, seg::rmq_cartesian<int>)->Range(1024, 256 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_TEMPLATE(BM_RMQ_RandomAll, seg::baseline::rmq_slow<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomAll, seg::rmq_compact<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomAll, seg::rmq_fast<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomAll, seg::rmq_cartesian<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
