# jwbind

Jwbind is a tool to transpile simple Java classes from source code into C++ classes. 

Note that jwbind aims to explore the capability to make the wrapper classes act like equivalent Java classes rather than mapping source code from Java to C++ based on Wasm binary.

## Usage
```
make            # deploy the toolchain
make test       # run tests

./jwbind <filepath>
```

## Requirements
1. Gradle
2. JDK 8 or above
3. CMake and GCC/Clang
4. python3

## Related projects
1. JWebAssembly
2. Wasm-micro-runtime
3. binaryen

## Overview

### Transpilation workflow
![arch](http://assets.processon.com/chart_image/604c741763768958e99a04cf.png)

### Client view
![client-view](http://assets.processon.com/chart_image/5ffed9cfe401fd661a3d2542.png)

