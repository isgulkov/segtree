#include <benchmark/benchmark.h>

#include "models/rmq_slow.hpp"
#include "rmq_fast.hpp"
#include "rmq_compact.hpp"

template<typename RMQ>
void BM_RMQ_Bad(benchmark::State& state) {
    std::vector<int> xs;
    xs.reserve(state.range(0));

    for(int i = 0; i < state.range(0); i++) {
        xs.push_back(i);
    }

    RMQ rmq(xs);

    for(auto _ : state) {
        for(int i = 0; i < state.range(0); i++) {
            for(int j = i + 1; j < state.range(0); j++) {
                benchmark::DoNotOptimize(rmq.get(i, j));
            }
        }
    }
}

BENCHMARK_TEMPLATE(BM_RMQ_Bad, seg::models::rmq_slow<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_Bad, seg::rmq_compact<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);
BENCHMARK_TEMPLATE(BM_RMQ_Bad, seg::rmq_fast<int>)->Range(64, 4 * 1024)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
