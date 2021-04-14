#include "HelloRef.h"

int32_t HelloRef::add2(int32_t a, int32_t b) { return a + b; }
int32_t HelloRef::add3(int32_t a, int32_t b, int32_t c) { return a + b + c; }
float HelloRef::fadd2(float a, float b) { return a + b; }
double HelloRef::dadd2(double a, double b) { return a + b; }
int64_t HelloRef::ladd2(int64_t a, int64_t b) { return a + b; }
int32_t HelloRef::getn() { return n; }
void HelloRef::setn(int32_t val) { n = val; }