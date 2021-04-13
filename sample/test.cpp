#include "HelloWorld.h"

#include <cassert>

#define ASSERT_EQUAL(a, b) do { \
    assert((a) == (b)); \
} while (0);

int main() {
    HelloWorld hello;
    printf("\n\nstart testing...\n");

    ASSERT_EQUAL(HelloWorld::add2(1,2), 3);
    ASSERT_EQUAL(hello.add3(1,2,3), 6);
    ASSERT_EQUAL(hello.fadd2(10,11), 21);
    ASSERT_EQUAL(hello.dadd2(20,11), 31);
    ASSERT_EQUAL(hello.ladd2(20000,11), 20011);
    hello.setn(1000);
    ASSERT_EQUAL(hello.getn(), 1000);

    printf("all tests passed.\n");
    
    return 0;
}