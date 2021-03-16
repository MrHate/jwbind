default: deploy

deploy:
	git submodule update --init
	cd java/jwasm && make

clean::
	rm -f *.h *.cpp *.wasm *.a *.so
	rm -rf .jwbind

