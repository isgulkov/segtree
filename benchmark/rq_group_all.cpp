#include <benchmark/benchmark.h>

#include "bench_util.hpp"

#include "baseline/segtree_slow.hpp"
#include "rq_group.hpp"

template<typename RQ>
void BM_RQGroup_RandomAll(benchmark::State& state) {
    std::vector<int> xs = random_ints(state.range(0));

    RQ rq(xs);

    for(auto _ : state) {
        for(int i = 0; i < rq.size(); i++) {
            for(int j = i + 1; j < rq.size(); j++) {
                benchmark::DoNotOptimize(rq.get(i, j));
            }
        }
    }
}

BENCHMARK_TEMPLATE(BM_RQGroup_RandomAll, seg::baseline::segtree_slow<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RQGroup_RandomAll, seg::rq_group<int>)->Range(64, 64 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
