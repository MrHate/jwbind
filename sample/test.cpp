#include "HelloWorld.h"

#include <cassert>
#include <cmath>
#include <ctime>

#define ITER_NUM 10000

#define ASSERT_EQUAL(a, b) do { \
    if((a) == (b)) break; \
    fprintf(stderr, "Line: %d assertion failed\n", __LINE__); \
    fflush(stderr); \
    exit(EXIT_FAILURE); \
} while (0);

const char *PRINT_GREEN = "\033[92m";
const char *PRINT_RESET = "\033[0m";
const char *LOG_PREFIX = "[jwbind-test]";

int32_t acc(int32_t a) {
    int sum = 0;
    while(a > 0) {
        sum += a--;
    }
    return sum;
}

int main() {
    HelloWorld hello;
    printf("\n\n%s%s Start testing...%s\n", PRINT_GREEN, LOG_PREFIX,
           PRINT_RESET);
    srand(time(0));

    // Check default value.
    ASSERT_EQUAL(hello.getn(), 18);

    // Basic addition test cases under different argument types.
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


    // Advanced function test cases
    for (int32_t i = 0; i < 10; ++i) {
      // Since the stack size is set to 8092 default, the recursion level cannot
      // be too large.
      int32_t a = rand() % 20;
      ASSERT_EQUAL(hello.recursive_sum(a), acc(a));
    }
    for (int32_t i = 0; i < 10; ++i) {
      int32_t a = rand() % 100;
      ASSERT_EQUAL(hello.loop_sum(a), acc(a));
    }

    printf("%s%s All tests passed.%s\n", PRINT_GREEN, LOG_PREFIX, PRINT_RESET);

    return 0;
}