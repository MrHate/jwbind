# jwbind

Jwbind is a toolchain to transpile simple Java classes from source code into C++ classes. 

Note that jwbind aims to explore the capability to make the wrapper classes act like equivalent Java classes rather than mapping source code from Java to C++ based on Wasm binary.

## Usage

```
make            # deploy the toolchain
make test       # run tests
make benchmark	# run benchmark

./jwbind <filepath>
```

## Requirements

* Gradle
* JDK 8 or above
* CMake and GCC/Clang
* python3

## Related projects

* JWebAssembly
* Wasm-micro-runtime
* binaryen

## Overview

### Transpilation workflow

![arch](http://assets.processon.com/chart_image/6076775d0791293688822148.png)

The jwbind toolchain consists of a front-end and a back-end. 

The front-end part modifies the Java source file with python tools at first as the preprocessing stage to have the source file meet the requirements of JWebAssembly. It then compiles Java source code into Java bytecode by any javac tool. Afterward, it parses the Java bytecode into Wasm binary and necessary jwbind class description data within a custom section by [customized JWebAsssembly](https://github.com/MrHate/JWebAssembly).

The back-end part parses the Wasm module with binaryen to extract the class description data. Finally, the jwbind python tools would generate target wrapper source files and build the target archive/library file with the WAMR library altogether.

### Client view
![client-view](http://assets.processon.com/chart_image/5ffed9cfe401fd661a3d2542.png)

One of the jwbind output files is the class header. As shown below, it hides as much as possible implementation details behind the wrapper. Run `make test && cd out`, and you'll find it.

```c++
#include "simple.h"

class HelloWorld : public SimpleWrapper {
public:
	HelloWorld(): SimpleWrapper("HelloWorld.wasm") {}

	static int32_t add2(int32_t, int32_t);
	int32_t add3(int32_t, int32_t, int32_t);
	float fadd2(float, float);
	double dadd2(double, double);
	int64_t ladd2(int64_t, int64_t);
	int32_t getn();
	void setn(int32_t);

	static HelloWorld& staticInstance() {
		static HelloWorld _inst;
		return _inst;
	}
};
```

### Benchmark

Although jwbind wrapper classes suffer terrible performance, there is still a benchmark analysis and optimization inspiration [here](./cpp/benchmark/README.md).

