## jwbind-benchmark

### Phase 1: No optimiation

No optimazation provided, ran on Apr. 14, 2021:

```
Run on (16 X 2100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x16)
  L1 Instruction 32 KiB (x16)
  L2 Unified 4096 KiB (x16)
  L3 Unified 16384 KiB (x16)
Load Average: 8.10, 12.77, 6.04
---------------------------------------------------------------
Benchmark                     Time             CPU   Iterations
---------------------------------------------------------------
RefCreation               0.000 ns        0.000 ns   1000000000
StaticI32Add2_Ref          1.37 ns         1.37 ns    442541832
NonStaticI32Add3_Ref       1.74 ns         1.74 ns    405971406
NonStaticF32Add2_Ref       1.74 ns         1.74 ns    402798302
NonStaticF64Add2_Ref       1.70 ns         1.70 ns    411566195
NonStaticI64Add2_Ref       1.95 ns         1.95 ns    416571059
NonStaticI32Set_Ref        1.99 ns         1.99 ns    350117725
NonStaticI32Get_Ref        1.92 ns         1.92 ns    339640486
WrapperCreation          103504 ns       103392 ns         6739
StaticI32Add2             27981 ns        27919 ns        24957
NonStaticI32Add3          28301 ns        28241 ns        24718
NonStaticF32Add2          30017 ns        29927 ns        23758
NonStaticF64Add2          29134 ns        29074 ns        23113
NonStaticI64Add2          28510 ns        28447 ns        24520
NonStaticI32Set           28322 ns        28260 ns        24765
NonStaticI32Get           28045 ns        27978 ns        25125
```