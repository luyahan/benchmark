#include "deps/include/benchmark/benchmark.h"
#include <cmath>


// // 测试浮点加法延迟 (FAdd)
// static void BM_FAdd_Latency(benchmark::State& state) {
//     float x = 1.1f;
//     float y = 1.0001f;

//     for (auto _ : state) {
//         __asm__ __volatile__(
//             "addss %1, %0\n\t"
//             "addss %1, %0\n\t"
//             "addss %1, %0\n\t"
//             "addss %1, %0\n\t"
//             "addss %1, %0\n\t"
//             "addss %1, %0\n\t"
//             "addss %1, %0\n\t"
//             "addss %1, %0\n\t"
//             "addss %1, %0\n\t"
//             "addss %1, %0\n\t"
//             "addss %1, %0\n\t"
//             "addss %1, %0"
//             : "+x"(x)
//             : "x"(y)
//         );
//         benchmark::DoNotOptimize(x);
//     }
//     state.SetItemsProcessed(state.iterations() * 12);
// }
// BENCHMARK(BM_FAdd_Latency);

// 测试整数加法延迟 (IAdd)
static void BM_IAdd_Latency(benchmark::State& state) {
    volatile int64_t x = 1;
    int64_t y = 1234567;

    for (auto _ : state) {
        x += y; x += y; x += y; x += y;
        x += y; x += y; x += y; x += y;
        x += y; x += y; x += y; x += y;
        benchmark::DoNotOptimize(x);
    }
    state.SetItemsProcessed(state.iterations() * 12);
}
BENCHMARK(BM_IAdd_Latency);

// 测试整数乘法延迟 (IMul)
static void BM_IMul_Latency(benchmark::State& state) {
    volatile int64_t x = 1234567;
    int64_t y = 7654321;

    for (auto _ : state) {
        x *= y; x *= y; x *= y; x *= y;
        x *= y; x *= y; x *= y; x *= y;
        x *= y; x *= y; x *= y; x *= y;
        benchmark::DoNotOptimize(x);
    }
    state.SetItemsProcessed(state.iterations() * 12);
}
BENCHMARK(BM_IMul_Latency);

// 测试除法延迟 (IDiv)
static void BM_IDiv_Latency(benchmark::State& state) {
    volatile int64_t x = 1234567;
    const int64_t y = 42;

    for (auto _ : state) {
        x /= y; x /= y; x /= y; x /= y;
        x /= y; x /= y; x /= y; x /= y;
        x /= y; x /= y; x /= y; x /= y;
        benchmark::DoNotOptimize(x);
    }
    state.SetItemsProcessed(state.iterations() * 12);
}
BENCHMARK(BM_IDiv_Latency);

// 测试浮点乘法延迟 (FMul)
static void BM_FMul_Latency(benchmark::State& state) {
    volatile float x = 1.1f;
    float y = 2.5f;

    for (auto _ : state) {
        x *= y; x *= y; x *= y; x *= y;
        x *= y; x *= y; x *= y; x *= y;
        x *= y; x *= y; x *= y; x *= y;
        benchmark::DoNotOptimize(x);
    }
    state.SetItemsProcessed(state.iterations() * 12);
}
BENCHMARK(BM_FMul_Latency);

// 测试除法延迟 (FDiv)
static void BM_FDiv_Latency(benchmark::State& state) {
    volatile float x = 1.1f;
    const float y = 3.0f;

    for (auto _ : state) {
        x /= y; x /= y; x /= y; x /= y;
        x /= y; x /= y; x /= y; x /= y;
        x /= y; x /= y; x /= y; x /= y;
        benchmark::DoNotOptimize(x);
    }
    state.SetItemsProcessed(state.iterations() * 12);
}
BENCHMARK(BM_FDiv_Latency);

// 测试平方根延迟 (FSqrt)
static void BM_FSqrt_Latency(benchmark::State& state) {
    volatile float x = 1.1f;

    for (auto _ : state) {
        x = sqrtf(x);
        benchmark::DoNotOptimize(x);
    }
    state.SetItemsProcessed(state.iterations());
}
BENCHMARK(BM_FSqrt_Latency);

// 测试内存加载延迟 (Load)
static void BM_Load_Latency(benchmark::State& state) {
    alignas(64) static int64_t arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    volatile int64_t sum = 0;

    for (auto _ : state) {
        sum += arr[0];
        sum += arr[1];
        sum += arr[2];
        sum += arr[3];
        sum += arr[4];
        sum += arr[5];
        sum += arr[6];
        sum += arr[7];
        sum += arr[0];
        sum += arr[1];
        sum += arr[2];
        sum += arr[3];
        benchmark::DoNotOptimize(sum);
    }
    state.SetItemsProcessed(state.iterations() * 12);
}
BENCHMARK(BM_Load_Latency);

// 测试分支预测失败惩罚
static void BM_BranchMiss_Latency(benchmark::State& state) {
    volatile int64_t x = 0;
    bool condition = false;

    for (auto _ : state) {
        for (int i = 0; i < 12; ++i) {
            condition = !condition;
            if (condition) {
                x += 1;
            } else {
                x += 2;
            }
        }
        benchmark::DoNotOptimize(x);
    }
    state.SetItemsProcessed(state.iterations() * 12);
}
BENCHMARK(BM_BranchMiss_Latency);

BENCHMARK_MAIN();
