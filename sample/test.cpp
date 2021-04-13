#include "HelloWorld.h"

#include <cassert>

#define ASSERT_EQUAL(a, b) do { \
    assert((a) == (b)); \
} while (0);

int main() {
    // HelloWorld mm;
    printf("\n\nstart testing...\n");

    ASSERT_EQUAL(HelloWorld::add2(1,2), 3);
    ASSERT_EQUAL(HelloWorld::add3(1,2,3), 6);
    ASSERT_EQUAL(HelloWorld::fadd2(10,11), 21);
    ASSERT_EQUAL(HelloWorld::dadd2(20,11), 31);
    ASSERT_EQUAL(HelloWorld::ladd2(20000,11), 20011);
    HelloWorld::setn(1000);
    ASSERT_EQUAL(HelloWorld::getn(), 1000);

    printf("all tests passed.\n");
    
    return 0;
}