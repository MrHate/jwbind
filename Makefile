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
	cd cpp && mkdir build && cd build && cmake .. && make -j

clean::
	rm -f *.h *.cpp *.wasm *.a *.so
	rm -rf .jwbind

