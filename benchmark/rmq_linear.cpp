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

    for(auto _ : state) {
        for(int i = 0; i < rmq.size() - 3; i++) {
            benchmark::DoNotOptimize(rmq.get(i, i + 3));
        }

        for(int i = 0; i < rmq.size() / 2; i++) {
            benchmark::DoNotOptimize(rmq.get(i, rmq.size() - i));
        }

        for(int i = rmq.size() - 1; i >= 0; i--) {
            benchmark::DoNotOptimize(rmq.get(i, rmq.size()));
        }
    }
}

BENCHMARK_TEMPLATE(BM_RMQ_RandomLinear, seg::baseline::rmq_slow<int>)->Range(64, 32 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomLinear, seg::rmq_fast<int>)->Range(64, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomLinear, seg::rmq_cartesian<int>)->Range(64, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomLinear, seg::segtree_min<int>)->Range(64, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
