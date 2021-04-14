default: deploy

deploy: download-submmodules build-jwasm build-cpp-tools

download-submmodules:
	git submodule update --init

build-jwasm: build-jwasm-api build-jwasm-gradle
	cd java/jwasm && gradle publishToMavenLocal

build-jwasm-api:
	cd java/jwasm-api && gradle jar

build-jwasm-gradle:
	cd java/jwasm-gradle && gradle jar

build-cpp-tools:
	test -d cpp/build || (cd cpp && mkdir build && cd build && cmake .. && make -j)

clean::
	rm -f *.h *.cpp *.wasm
	rm -rf .jwbind
	rm -rf out

test:: clean deploy
	./jwbind sample/HelloWorld.java
	cp sample/Makefile out
	cp sample/test.cpp out
	cd out && make -j && ./a.out

benchmark:: deploy
	./cpp/build/out/jwbind-benchmark