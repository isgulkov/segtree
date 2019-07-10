#include <cmath>

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

    state.SetComplexityN(state.range(0));
}

template<typename RQ>
void BM_RQMode_RandomConstant(benchmark::State& state) {
    std::vector<int> xs = random_ints_few(state.range(0));

    RQ rq(xs);

    for(auto _ : state) {
        state.PauseTiming();
        const auto ps = random_segments(1000, rq.size());
        state.ResumeTiming();

        for(const auto& p : ps) {
            benchmark::DoNotOptimize(rq.get(p.first, p.second));
        }
    }

    state.SetComplexityN(state.range(0));
}

BENCHMARK_TEMPLATE(BM_RQMode_RandomCreate, seg::baseline::rq_mode_slow<int>)->Range(64, 4 * 1024)->Complexity(benchmark::oN)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RQMode_RandomCreate, seg::rq_mode_fast<int>)->Range(64, 4 * 1024)->Complexity(benchmark::oNSquared)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RQMode_RandomCreate, seg::rq_mode_compact<int>)->Range(64, 4 * 1024)->Complexity([](auto n) { return std::pow(n, 1.5); })->Unit(benchmark::kMillisecond);

//->Repetitions(10)->ReportAggregatesOnly(true)
BENCHMARK_TEMPLATE(BM_RQMode_RandomConstant, seg::baseline::rq_mode_slow<int>)->Range(64, 16 * 1024)->Complexity(benchmark::oN)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RQMode_RandomConstant, seg::rq_mode_fast<int>)->Range(64, 4 * 1024)->Complexity(benchmark::o1)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RQMode_RandomConstant, seg::rq_mode_compact<int>)->Range(64, 64 * 1024)->Complexity(std::sqrt)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
