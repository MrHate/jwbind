## jwbind-benchmark

Note that the cases named with "ref" are reference cases running equivalent methods written directly in C++.

### Phase 1: No optimiation

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

### Phase 2: hash-map function cache

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