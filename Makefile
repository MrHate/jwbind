default: deploy

deploy: download-submmodules build-jwasm

download-submmodules:
	git submodule update --init

build-jwasm: build-jwasm-api build-jwasm-gradle
	cd java/jwasm && gradle clean publishToMavenLocal

build-jwasm-api:
	cd java/jwasm-api && gradle clean jar

build-jwasm-gradle:
	cd java/jwasm-gradle && gradle clean jar

clean::
	rm -f *.h *.cpp *.wasm *.a *.so
	rm -rf .jwbind

