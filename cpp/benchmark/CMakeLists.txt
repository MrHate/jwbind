cmake_minimum_required(VERSION 3.10.2)
project(jwbind-benchmark LANGUAGES C CXX VERSION 100)

set(CMAKE_CXX_STANDARD 14)

# find_package(benchmark REQUIRED)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out )
add_executable(jwbind-benchmark src/jbenchmark.cpp)
target_link_libraries(jwbind-benchmark benchmark::benchmark)