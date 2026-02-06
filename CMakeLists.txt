cmake_minimum_required(VERSION 3.16)
project(InstructionLatency LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 使用 google benchmark submodule (禁用GTest)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(deps/benchmark)

add_executable(benchmark_latency
    main.cpp
)

target_link_libraries(benchmark_latency
    benchmark::benchmark
    benchmark::benchmark_main
)

# 编译选项
target_compile_options(benchmark_latency PRIVATE
    -O2
    -march=native
)
