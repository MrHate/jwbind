#include <cstdint>

class HelloRef {
    int32_t n;
public:
    HelloRef():n(0){}
    
	static int32_t add2(int32_t, int32_t);
	int32_t add3(int32_t, int32_t, int32_t);
	float fadd2(float, float);
	double dadd2(double, double);
	int64_t ladd2(int64_t, int64_t);
	int32_t getn();
	void setn(int32_t);
};