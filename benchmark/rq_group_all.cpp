#include <benchmark/benchmark.h>

#include "bench_util.hpp"

#include "baseline/segtree_slow.hpp"
#include "rq_group.hpp"
#include "segtree_semi.hpp"

template<typename RQ>
void BM_RQGroup_RandomLinear(benchmark::State& state) {
    std::vector<int> xs = random_ints(state.range(0));

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

BENCHMARK_TEMPLATE(BM_RQGroup_RandomLinear, seg::baseline::segtree_slow<int>)->Range(256, 256 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RQGroup_RandomLinear, seg::rq_group<int>)->Range(256, 256 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RQGroup_RandomLinear, seg::segtree_semi<int>)->Range(256, 256 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
