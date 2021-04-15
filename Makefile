default: deploy


# ================ build and deploy ====================

deploy: download-submmodules build-jwasm build-cpp-tools

download-submmodules:
	git submodule update --init -- java/jwasm
	git submodule update --init -- java/jwasm-api
	git submodule update --init -- java/jwasm-gradle
	git submodule update --init -- cpp/binaryen
	git submodule update --init -- cpp/wamr

build-jwasm: build-jwasm-api build-jwasm-gradle
	cd java/jwasm && gradle publishToMavenLocal

build-jwasm-api:
	cd java/jwasm-api && gradle jar

build-jwasm-gradle:
	cd java/jwasm-gradle && gradle jar

# Manually delete cpp/build to have the makefile rebuilt cpp tools.
# TODO: Save the time building unnecessary binaryen targets.
build-cpp-tools:
	test -d cpp/build || (cd cpp && mkdir build && cd build && cmake .. && make -j)


# ================ utility tasks ====================

clean::
	rm -f *.h *.cpp *.wasm
	rm -rf .jwbind
	rm -rf out

test:: clean deploy
	./jwbind sample/HelloWorld.java
	cp sample/Makefile out
	cp sample/test.cpp out
	cd out && make -j && ./a.out

benchmark:: test
	git submodule update --init -- cpp/benchmark/googlebenchmark
	cp -r out cpp/benchmark/
	cd cpp/benchmark && rm -rf build && mkdir build && cd build && cmake .. && make -j
	cd cpp/benchmark/out && ../build/jwbind-benchmark 