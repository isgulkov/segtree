cmake_minimum_required(VERSION 3.13)
project(segtree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native")

include_directories(include/)

add_executable(segtree main_segtree.cpp)
add_executable(rmq_static main_rmq_static.cpp)
add_executable(rq_group main_rq_group.cpp)
add_executable(mode main_mode.cpp)

#### Tests ####

add_subdirectory(vendor/googletest)
enable_testing()

add_executable(test_rmq test/rmq.cpp)
target_link_libraries(test_rmq PRIVATE gtest gtest_main)

add_executable(test_rq_group test/rq_group.cpp)
target_link_libraries(test_rq_group PRIVATE gtest gtest_main)

add_executable(test_util_math test/util_math.cpp)
target_link_libraries(test_util_math PRIVATE gtest gtest_main)

#### Benchmarks ####

set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(vendor/benchmark)

add_executable(bm_rmq_all benchmark/rmq_all.cpp)
target_link_libraries(bm_rmq_all PRIVATE benchmark)

add_executable(bm_rmq_linear benchmark/rmq_linear.cpp)
target_link_libraries(bm_rmq_linear PRIVATE benchmark)

add_executable(bm_rmq_create benchmark/rmq_create.cpp)
target_link_libraries(bm_rmq_create PRIVATE benchmark)

add_executable(bm_rq_group_linear benchmark/rq_group_linear.cpp)
target_link_libraries(bm_rq_group_linear PRIVATE benchmark)

add_executable(bm_sqrt_ceil benchmark/sqrt_ceil.cpp)
target_link_libraries(bm_sqrt_ceil PRIVATE benchmark)
