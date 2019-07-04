#include <benchmark/benchmark.h>

#include "bench_util.hpp"

#include "baseline/rmq_slow.hpp"
#include "rmq_fast.hpp"
#include "rmq_cartesian.hpp"
#include "segtree_semi.hpp"

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

BENCHMARK_TEMPLATE(BM_RMQ_RandomAll, seg::baseline::rmq_slow<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomAll, seg::rmq_fast<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomAll, seg::rmq_cartesian<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_RandomAll, seg::segtree_min<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
