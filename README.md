# jwbind

Jwbind is a toolchain to transpile simple Java classes from source code into C++ classes. 

Note that jwbind aims to explore the capability to make the wrapper classes act like equivalent Java classes rather than mapping source code from Java to C++ based on Wasm binary.

## Usage

```
make            # deploy the toolchain
make test       # run tests

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

![arch](http://assets.processon.com/chart_image/604c741763768958e99a04cf.png)

The jwbind toolchain consists of a front-end and a back-end. 

The front-end part modifies the Java source file with [jparser.py](./pytool/jparser.py) at first as the preprocessing stage to have the source file meet the requirements of JWebAssembly. It then compiles Java source code into Java bytecode by any javac tool. Afterward, it parses the Java bytecode into Wasm binary and necessary jwbind class description data within a custom section by [customized JWebAsssembly](https://github.com/MrHate/JWebAssembly).

The back-end part parses the Wasm module with binaryen to extract the class description data. Finally, the jwbind python tools would generate target wrapper source files and build the target archive/library file with the WAMR library altogether.

### Client view
![client-view](http://assets.processon.com/chart_image/5ffed9cfe401fd661a3d2542.png)

