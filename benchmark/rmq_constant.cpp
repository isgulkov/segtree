#include <benchmark/benchmark.h>

#include "bench_util.hpp"

#include "baseline/rmq_slow.hpp"
#include "rmq_fast.hpp"
#include "rmq_cartesian.hpp"
#include "segtree_semi.hpp"

template<typename RMQ>
void BM_RMQ_RandomLinear(benchmark::State& state) {
    std::vector<int> xs = random_ints_bin(state.range(0));

    RMQ rmq(xs);

    const auto ps = random_segments(10000, rmq.size());

    for(auto _ : state) {
        for(const auto& p : ps) {
            benchmark::DoNotOptimize(rmq.get(p.first, p.second));
        }
    }

    state.SetComplexityN(state.range(0));
}

/**
 * NOTE: The current implementation of rmq_cartesian is unacceptably slow: it's only faster than segtree for values of
 *       values of N over ~32M.
 */

BENCHMARK_TEMPLATE(BM_RMQ_RandomLinear, seg::baseline::rmq_slow<int>)->Range(64, 32 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomLinear, seg::rmq_fast<int>)->Range(64, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomLinear, seg::rmq_cartesian<int>)->Range(64, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomLinear, seg::segtree_min<int>)->Range(64, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
