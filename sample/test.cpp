#include "HelloWorld.h"

#include <cassert>
#include <cmath>
#include <ctime>

#define ITER_NUM 100

#define ASSERT_EQUAL(a, b) do { \
    if((a) == (b)) break; \
    fprintf(stderr, "Line: %d assertion failed\n", __LINE__); \
    fflush(stderr); \
    exit(EXIT_FAILURE); \
} while (0);

int main() {
    HelloWorld hello;
    printf("\n\n[jwbind basic tests]\tstart testing...\n");
    srand(time(0));

    for(int32_t i = 0; i < ITER_NUM; ++i) {
        int32_t a = rand() % 10000,
            b = rand() % 10000,
            c = a + b;
        ASSERT_EQUAL(HelloWorld::add2(a, b), c);
    }
    for(int32_t i = 0; i < ITER_NUM; ++i) {
        int32_t a = rand() % 10000,
            b = rand() % 10000,
            c = rand() % 10000,
            d = a + b + c;
        ASSERT_EQUAL(hello.add3(a, b, c), d);
    }
    for(int32_t i = 0; i < ITER_NUM; ++i) {
        float a = rand() % 10000 / 100.0,
            b = rand() % 10000 / 100.0,
            c = a + b;
        ASSERT_EQUAL(hello.fadd2(a, b), c);
    }
    for(int32_t i = 0; i < ITER_NUM; ++i) {
        double a = rand() % 10000 / 1000.0,
            b = rand() % 10000 / 1000.0,
            c = a + b;
        ASSERT_EQUAL(hello.dadd2(a, b), c);
    }
    for(int32_t i = 0; i < ITER_NUM; ++i) {
        int64_t a = rand() % 10000000,
            b = rand() % 10000000,
            c = a + b;
        ASSERT_EQUAL(hello.ladd2(a, b), c);
    }
    for(int32_t i = 0; i < ITER_NUM; ++i) {
        int32_t a = rand() % 10000;
        hello.setn(a);
        ASSERT_EQUAL(hello.getn(), a);
    }

    printf("[jwbind basic tests]\tall tests passed.\n");
    
    return 0;
}