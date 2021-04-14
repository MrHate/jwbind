#include <benchmark/benchmark.h>
#include <HelloWorld.h>

static void BM_StringCreation(benchmark::State& state) {
  for (auto _ : state)
    std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
  HelloWorld::add2(1,2);
}
BENCHMARK(BM_StringCopy);

BENCHMARK_MAIN();