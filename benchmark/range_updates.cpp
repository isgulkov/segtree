#include <benchmark/benchmark.h>

#include "bench_util.hpp"

#include "baseline/semi_slow.hpp"
#include "segtree_lazy.hpp"
#include "fenwick_tree.hpp"

template<typename RQ>
void BM_RangeSet_RandomConstant(benchmark::State& state) {
    std::vector<int> xs = random_ints_bin(state.range(0));

    RQ rq(xs);

    const auto ps = random_range_vs(1000, rq.size());

    for(auto _ : state) {
        for(const auto& p : ps) {
            rq.set(std::get<0>(p), std::get<1>(p), std::get<2>(p));
        }

        state.PauseTiming();
        benchmark::DoNotOptimize(rq.get(0, 1));
        benchmark::DoNotOptimize(rq.get(rq.size() - 1, rq.size()));
        benchmark::DoNotOptimize(rq.get(0, rq.size()));
        state.ResumeTiming();
    }

    state.SetComplexityN(state.range(0));
}

template<typename RQ>
void BM_RangeHandleSet_RandomConstant(benchmark::State& state) {
    std::vector<int> xs = random_ints_bin(state.range(0));

    RQ rq(xs);

    const auto ps = random_range_vs(1000, rq.size());

    for(auto _ : state) {
        for(const auto& p : ps) {
            rq[{ std::get<0>(p), std::get<1>(p) }] = std::get<2>(p);
        }

        state.PauseTiming();
        benchmark::DoNotOptimize(rq.get(0, 1));
        benchmark::DoNotOptimize(rq.get(rq.size() - 1, rq.size()));
        benchmark::DoNotOptimize(rq.get(0, rq.size()));
        state.ResumeTiming();
    }

    state.SetComplexityN(state.range(0));
}

template<typename RQ>
void BM_RangeAdd_RandomConstant(benchmark::State& state) {
    std::vector<int> xs = random_ints_bin(state.range(0));

    RQ rq(xs);

    const auto ps = random_range_vs(1000, rq.size());

    for(auto _ : state) {
        for(const auto& p : ps) {
            rq.add(std::get<0>(p), std::get<1>(p), std::get<2>(p));
        }

        state.PauseTiming();
        benchmark::DoNotOptimize(rq.get(0, 1));
        benchmark::DoNotOptimize(rq.get(rq.size() - 1, rq.size()));
        benchmark::DoNotOptimize(rq.get(0, rq.size()));
        state.ResumeTiming();
    }

    state.SetComplexityN(state.range(0));
}

template<typename RQ>
void BM_RangeHandleAdd_RandomConstant(benchmark::State& state) {
    std::vector<int> xs = random_ints_bin(state.range(0));

    RQ rq(xs);

    const auto ps = random_range_vs(1000, rq.size());

    for(auto _ : state) {
        for(const auto& p : ps) {
            rq[{ std::get<0>(p), std::get<1>(p) }] += std::get<2>(p);
        }

        state.PauseTiming();
        benchmark::DoNotOptimize(rq.get(0, 1));
        benchmark::DoNotOptimize(rq.get(rq.size() - 1, rq.size()));
        benchmark::DoNotOptimize(rq.get(0, rq.size()));
        state.ResumeTiming();
    }

    state.SetComplexityN(state.range(0));
}

BENCHMARK_TEMPLATE(BM_RangeSet_RandomConstant, seg::baseline::semi_slow<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
//BENCHMARK_TEMPLATE(BM_RangeSet_RandomConstant, seg::fenwick_tree<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RangeSet_RandomConstant, seg::segtree_lazy<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_TEMPLATE(BM_RangeHandleSet_RandomConstant, seg::baseline::semi_slow<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
//BENCHMARK_TEMPLATE(BM_RangeHandleSet_RandomConstant, seg::fenwick_tree<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RangeHandleSet_RandomConstant, seg::segtree_lazy<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_TEMPLATE(BM_RangeAdd_RandomConstant, seg::baseline::semi_slow<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
//BENCHMARK_TEMPLATE(BM_RangeAdd_RandomConstant, seg::fenwick_tree<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RangeAdd_RandomConstant, seg::segtree_lazy<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_TEMPLATE(BM_RangeHandleAdd_RandomConstant, seg::baseline::semi_slow<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
//BENCHMARK_TEMPLATE(BM_RangeHandleAdd_RandomConstant, seg::fenwick_tree<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RangeHandleAdd_RandomConstant, seg::segtree_lazy<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
