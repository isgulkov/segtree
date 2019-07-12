#include <benchmark/benchmark.h>

#include "bench_util.hpp"

#include "baseline/semi_slow.hpp"
#include "segtree_semi.hpp"
#include "fenwick_tree.hpp"

template<typename RQ>
void BM_PointSet_RandomConstant(benchmark::State& state) {
    std::vector<int> xs = random_ints_bin(state.range(0));

    RQ rq(xs);

    const auto ps = random_point_vs(10000, rq.size());

    for(auto _ : state) {
        for(const auto& p : ps) {
            rq.set(p.first, p.second);
        }

        benchmark::DoNotOptimize(rq.get(0, 1));
        benchmark::DoNotOptimize(rq.get(rq.size() - 1, rq.size()));
    }
}

template<typename RQ>
void BM_PointElemSet_RandomConstant(benchmark::State& state) {
    std::vector<int> xs = random_ints_bin(state.range(0));

    RQ rq(xs);

    const auto ps = random_point_vs(10000, rq.size());

    for(auto _ : state) {
        for(const auto& p : ps) {
            rq[p.first] = p.second;
        }

        state.PauseTiming();
        benchmark::DoNotOptimize(rq.get(0, 1));
        benchmark::DoNotOptimize(rq.get(rq.size() - 1, rq.size()));
        benchmark::DoNotOptimize(rq.get(0, rq.size()));
        state.ResumeTiming();
    }
}

BENCHMARK_TEMPLATE(BM_PointSet_RandomConstant, seg::baseline::semi_slow<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_PointSet_RandomConstant, seg::fenwick_tree<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_PointSet_RandomConstant, seg::segtree_semi<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_TEMPLATE(BM_PointElemSet_RandomConstant, seg::baseline::semi_slow<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_PointElemSet_RandomConstant, seg::fenwick_tree<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_PointElemSet_RandomConstant, seg::segtree_semi<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
