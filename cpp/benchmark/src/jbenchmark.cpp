#include <benchmark/benchmark.h>
#include <HelloWorld.h>
#include "HelloRef.h"


// ====================== Reference cases ======================

static void RefCreation(benchmark::State& state) {
  for (auto _ : state)
    HelloRef hello;
}
BENCHMARK(RefCreation);

static void StaticI32Add2_Ref(benchmark::State& state) {
  for (auto _ : state)
    HelloRef::add2(1,2);
}
BENCHMARK(StaticI32Add2_Ref);

static void NonStaticI32Add3_Ref(benchmark::State& state) {
  HelloRef hello;
  for (auto _ : state)
    hello.add3(1,2,3);
}
BENCHMARK(NonStaticI32Add3_Ref);

static void NonStaticF32Add2_Ref(benchmark::State& state) {
  HelloRef hello;
  for (auto _ : state)
    hello.fadd2(1.0,2.0);
}
BENCHMARK(NonStaticF32Add2_Ref);

static void NonStaticF64Add2_Ref(benchmark::State& state) {
  HelloRef hello;
  for (auto _ : state)
    hello.dadd2(1.0,2.0);
}
BENCHMARK(NonStaticF64Add2_Ref);

static void NonStaticI64Add2_Ref(benchmark::State& state) {
  HelloRef hello;
  for (auto _ : state)
    hello.ladd2(1,2);
}
BENCHMARK(NonStaticI64Add2_Ref);

static void NonStaticI32Set_Ref(benchmark::State& state) {
  HelloRef hello;
  for (auto _ : state)
    hello.setn(1);
}
BENCHMARK(NonStaticI32Set_Ref);

static void NonStaticI32Get_Ref(benchmark::State& state) {
  HelloRef hello;
  for (auto _ : state)
    hello.getn();
}
BENCHMARK(NonStaticI32Get_Ref);


// ====================== Wrapper cases ======================

static void WrapperCreation(benchmark::State& state) {
  for (auto _ : state)
    HelloWorld hello;
}
BENCHMARK(WrapperCreation);

static void StaticI32Add2(benchmark::State& state) {
  for (auto _ : state)
    HelloWorld::add2(1,2);
}
BENCHMARK(StaticI32Add2);

static void NonStaticI32Add3(benchmark::State& state) {
  HelloWorld hello;
  for (auto _ : state)
    hello.add3(1,2,3);
}
BENCHMARK(NonStaticI32Add3);

static void NonStaticF32Add2(benchmark::State& state) {
  HelloWorld hello;
  for (auto _ : state)
    hello.fadd2(1.0,2.0);
}
BENCHMARK(NonStaticF32Add2);

static void NonStaticF64Add2(benchmark::State& state) {
  HelloWorld hello;
  for (auto _ : state)
    hello.dadd2(1.0,2.0);
}
BENCHMARK(NonStaticF64Add2);

static void NonStaticI64Add2(benchmark::State& state) {
  HelloWorld hello;
  for (auto _ : state)
    hello.ladd2(1,2);
}
BENCHMARK(NonStaticI64Add2);

static void NonStaticI32Set(benchmark::State& state) {
  HelloWorld hello;
  for (auto _ : state)
    hello.setn(1);
}
BENCHMARK(NonStaticI32Set);

static void NonStaticI32Get(benchmark::State& state) {
  HelloWorld hello;
  for (auto _ : state)
    hello.getn();
}
BENCHMARK(NonStaticI32Get);

BENCHMARK_MAIN();