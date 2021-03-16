default::
	gradle -DsocksProxyHost=127.0.0.1 -DsocksProxyPort=1080 clean wasm

wat::
	wasm2wat -v --no-check --enable-reference-types ./build/distributions/jwasmtest.wasm -o jwasmtest.wat

objdump::
	wasm-objdump -s ./build/distributions/jwasmtest.wasm

