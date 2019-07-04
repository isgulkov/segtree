#include <benchmark/benchmark.h>

#include "bench_util.hpp"

#include "baseline/rmq_slow.hpp"
#include "rmq_fast.hpp"
#include "rmq_cartesian.hpp"
#include "segtree_semi.hpp"

template<typename RMQ>
void BM_RMQ_RandomCreate(benchmark::State& state) {
    std::vector<int> xs = random_ints(state.range(0));

    for(auto _ : state) {
        RMQ rmq(xs);

        benchmark::DoNotOptimize(rmq.get(0, 1));
    }
}

BENCHMARK_TEMPLATE(BM_RMQ_RandomCreate, seg::baseline::rmq_slow<int>)->Range(1024, 256 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomCreate, seg::rmq_fast<int>)->Range(1024, 256 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomCreate, seg::rmq_cartesian<int>)->Range(1024, 256 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomCreate, seg::segtree_min<int>)->Range(1024, 256 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
