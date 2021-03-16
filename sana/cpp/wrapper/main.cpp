#include <iostream>

#include "test.h"
#include "simple.h"

// class hello: public SimpleWrapper {
// public:
//   hello(): SimpleWrapper("../test.wasm") {}
//   int32_t getn() {
//     ArgVec args;
//     InvokeMethod("getn", args, 1);
//     assert(args.size());
//     return args[0].of.i32;
//   }
//   void setn(int32_t nn) {
//     ArgVec args;
//     args.push_back(WrapArg(nn));
//     InvokeMethod("setn", args, 0);
//   }
// };

int main() {
  test m;
  std::cout << m.getn() << std::endl;
  m.setn(10);
  std::cout << m.getn() << std::endl;
  return 0;
}
