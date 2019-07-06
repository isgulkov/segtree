#include <benchmark/benchmark.h>

#include "bench_util.hpp"

#include "baseline/rq_mode_slow.hpp"
#include "rq_mode_fast.hpp"
#include "rq_mode_compact.hpp"

template<typename RQ>
void BM_RQMode_RandomCreate(benchmark::State& state) {
    std::vector<int> xs = random_ints_few(state.range(0));

    for(auto _ : state) {
        RQ rq(xs);

        benchmark::DoNotOptimize(rq.get(0, 1));
        benchmark::DoNotOptimize(rq.get(0, rq.size() / 2));
        benchmark::DoNotOptimize(rq.get(0, rq.size()));
    }
}

template<typename RQ>
void BM_RQMode_RandomLinear(benchmark::State& state) {
    std::vector<int> xs = random_ints_few(state.range(0));

    RQ rq(xs);

    for(auto _ : state) {
        for(int i = 0; i < rq.size() - 3; i++) {
            benchmark::DoNotOptimize(rq.get(i, i + 3));
        }

        for(int i = 0; i < rq.size() / 2; i++) {
            benchmark::DoNotOptimize(rq.get(i, rq.size() - i));
        }

        for(int i = rq.size() - 1; i >= 0; i--) {
            benchmark::DoNotOptimize(rq.get(i, rq.size()));
        }
    }
}

BENCHMARK_TEMPLATE(BM_RQMode_RandomCreate, seg::baseline::rq_mode_slow<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RQMode_RandomCreate, seg::rq_mode_fast<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RQMode_RandomCreate, seg::rq_mode_compact<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_TEMPLATE(BM_RQMode_RandomLinear, seg::baseline::rq_mode_slow<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RQMode_RandomLinear, seg::rq_mode_fast<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RQMode_RandomLinear, seg::rq_mode_compact<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
