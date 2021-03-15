#include "simple.h"

class test : public SimpleWrapper {
public:
	test(): SimpleWrapper("../test.wasm") {}
	int32_t getn();
	void setn(int32_t);
};
