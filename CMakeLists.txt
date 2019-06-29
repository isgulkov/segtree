cmake_minimum_required(VERSION 3.13)
project(segtree)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/)

add_executable(segtree main_segtree.cpp)
add_executable(rmq_static main_rmq_static.cpp)

# Benchmarks

set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(vendor/benchmark)

add_executable(bench_rmq benchmark/rmq.cpp)
target_link_libraries(bench_rmq PRIVATE benchmark)
