## jwbind-benchmark

Note that the cases named with "ref" are reference cases running equivalent methods written directly in C++.

### Phase 0: No optimiation

```
Run on (16 X 2100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x16)
  L1 Instruction 32 KiB (x16)
  L2 Unified 4096 KiB (x16)
  L3 Unified 16384 KiB (x16)
Load Average: 2.26, 0.73, 0.52
---------------------------------------------------------------
Benchmark                     Time             CPU   Iterations
---------------------------------------------------------------
RefCreation               0.000 ns        0.000 ns   1000000000
StaticI32Add2_Ref          1.38 ns         1.38 ns    446441968
NonStaticI32Add3_Ref       1.73 ns         1.73 ns    406586020
NonStaticF32Add2_Ref       1.73 ns         1.73 ns    406884438
NonStaticF64Add2_Ref       1.72 ns         1.72 ns    404061786
NonStaticI64Add2_Ref       1.77 ns         1.77 ns    398895768
NonStaticI32Set_Ref        1.72 ns         1.72 ns    407783530
NonStaticI32Get_Ref        1.72 ns         1.72 ns    403974598
WrapperCreation          110530 ns       110429 ns         6230
StaticI32Add2             30792 ns        30733 ns        21729
NonStaticI32Add3          28914 ns        28863 ns        24331
NonStaticF32Add2          28558 ns        28449 ns        24132
NonStaticF64Add2          28806 ns        28734 ns        24552
NonStaticI64Add2          28647 ns        28595 ns        24532
NonStaticI32Set           28594 ns        28470 ns        24626
NonStaticI32Get           28361 ns        28309 ns        24807
```

### Phase 1: Hashmap function cache

WAMR looks up functions by traversing a list that features a linear seeking time O(n).
As Wrappers pass the same pointers to WAMR to look up for the same functions, using hashmaps to cache function handles provides a hopefully O(1) seeking time, along with, however, more extended construction and destruction time.

```
Run on (16 X 2100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x16)
  L1 Instruction 32 KiB (x16)
  L2 Unified 4096 KiB (x16)
  L3 Unified 16384 KiB (x16)
Load Average: 2.49, 0.82, 0.60
---------------------------------------------------------------
Benchmark                     Time             CPU   Iterations
---------------------------------------------------------------
RefCreation               0.000 ns        0.000 ns   1000000000
StaticI32Add2_Ref          1.79 ns         1.79 ns    312738817
NonStaticI32Add3_Ref       1.73 ns         1.73 ns    377073389
NonStaticF32Add2_Ref       1.43 ns         1.43 ns    504849643
NonStaticF64Add2_Ref       1.39 ns         1.39 ns    487661641
NonStaticI64Add2_Ref       1.73 ns         1.73 ns    400832336
NonStaticI32Set_Ref        1.59 ns         1.58 ns    402106939
NonStaticI32Get_Ref        1.84 ns         1.83 ns    366451607
WrapperCreation          118188 ns       117998 ns         6316
StaticI32Add2             31370 ns        31313 ns        23183
NonStaticI32Add3          28644 ns        28588 ns        20729
NonStaticF32Add2          28077 ns        28021 ns        24803
NonStaticF64Add2          28875 ns        28822 ns        24993
NonStaticI64Add2          29454 ns        29391 ns        22534
NonStaticI32Set           28993 ns        28918 ns        23576
NonStaticI32Get           29288 ns        29231 ns        23564
```

### Phase 2: Hashmap Wasm binary cache

As each wrapper object invokes a complete process from reading Wasm binary with file I/O to module instantiation during construction, providing a binary cache shall considerably improve the WrapperCreation score.

```
Run on (16 X 2100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x16)
  L1 Instruction 32 KiB (x16)
  L2 Unified 4096 KiB (x16)
  L3 Unified 16384 KiB (x16)
Load Average: 1.56, 0.63, 0.34
---------------------------------------------------------------
Benchmark                     Time             CPU   Iterations
---------------------------------------------------------------
RefCreation               0.000 ns        0.000 ns   1000000000
StaticI32Add2_Ref          1.38 ns         1.38 ns    457208576
NonStaticI32Add3_Ref       1.75 ns         1.75 ns    407099669
NonStaticF32Add2_Ref       1.73 ns         1.72 ns    398471944
NonStaticF64Add2_Ref       1.72 ns         1.72 ns    401396295
NonStaticI64Add2_Ref       1.68 ns         1.68 ns    416515055
NonStaticI32Set_Ref        1.68 ns         1.68 ns    415327594
NonStaticI32Get_Ref        1.70 ns         1.70 ns    416379682
WrapperCreation           31660 ns        31575 ns        20320
StaticI32Add2             30304 ns        30219 ns        22586
NonStaticI32Add3          30746 ns        30662 ns        21826
NonStaticF32Add2          30275 ns        30189 ns        22022
NonStaticF64Add2          29970 ns        29875 ns        22368
NonStaticI64Add2          31228 ns        31140 ns        21910
NonStaticI32Set           30251 ns        30165 ns        23339
NonStaticI32Get           31564 ns        31479 ns        23526
```

### Phase 3: Eliminate unnecessary memory allocation during arg wrapping

Each arg wrapper function previously triggers one std::vector construction and n*2 wasm_val_t constructions along with correlated destructions.
Such stuff could be eliminated by moving arg vector into member-static and adjusting arg value directly on arg vector passing by reference.

```
Run on (16 X 2100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x16)
  L1 Instruction 32 KiB (x16)
  L2 Unified 4096 KiB (x16)
  L3 Unified 16384 KiB (x16)
Load Average: 2.60, 1.64, 1.02
---------------------------------------------------------------
Benchmark                     Time             CPU   Iterations
---------------------------------------------------------------
RefCreation               0.000 ns        0.000 ns   1000000000
StaticI32Add2_Ref          1.40 ns         1.40 ns    357196200
NonStaticI32Add3_Ref       1.73 ns         1.73 ns    404634721
NonStaticF32Add2_Ref       1.73 ns         1.73 ns    405202429
NonStaticF64Add2_Ref       1.73 ns         1.73 ns    405354713
NonStaticI64Add2_Ref       1.72 ns         1.72 ns    407806096
NonStaticI32Set_Ref        1.75 ns         1.75 ns    400254308
NonStaticI32Get_Ref        1.75 ns         1.75 ns    403759052
WrapperCreation           29901 ns        29841 ns        23489
StaticI32Add2             26844 ns        26784 ns        25262
NonStaticI32Add3          28723 ns        28636 ns        21997
NonStaticF32Add2          29978 ns        29908 ns        24101
NonStaticF64Add2          28646 ns        28572 ns        23113
NonStaticI64Add2          29239 ns        29155 ns        23694
NonStaticI32Set           29630 ns        29544 ns        23541
NonStaticI32Get           29037 ns        28956 ns        23249
```