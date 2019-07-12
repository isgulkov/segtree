#include <benchmark/benchmark.h>

#include "bench_util.hpp"

#include "baseline/semi_slow.hpp"
#include "rq_group.hpp"
#include "segtree_semi.hpp"
#include "fenwick_tree.hpp"

template<typename RQ>
void BM_RQGroup_RandomLinear(benchmark::State& state) {
    std::vector<int> xs = random_ints_bin(state.range(0));

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

BENCHMARK_TEMPLATE(BM_RQGroup_RandomLinear, seg::baseline::semi_slow<int>)->Range(256, 32 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RQGroup_RandomLinear, seg::rq_group<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RQGroup_RandomLinear, seg::fenwick_tree<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RQGroup_RandomLinear, seg::segtree_sum<int>)->Range(256, 4 * 1024 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
