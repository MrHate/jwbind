#include "HelloWorld.h"

#include <cassert>

int main() {
    HelloWorld mm;
    assert(HelloWorld::add2(1,2) == 3);
    assert(mm.add3(1,2,3) == 6);
    assert(mm.fadd2(10,11) == 21);
    assert(mm.dadd2(20,11) == 31);
    assert(mm.ladd2(20000,11) == 20011);
    mm.setn(1000);
    assert(mm.getn() == 1000);
    
    return 0;
}