#include "test.h"

int32_t test::getn() {
	ArgVec args;
	InvokeMethod("getn", args, 1);
	return args[0].of.i32;
}

void test::setn(int32_t arg0) {
	ArgVec args;
	args.push_back(WrapArg(arg0));
	InvokeMethod("setn", args, 0);
}

