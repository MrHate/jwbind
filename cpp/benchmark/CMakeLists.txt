cmake_minimum_required(VERSION 3.10.2)
project(jwbind-benchmark LANGUAGES C CXX VERSION 100)

set(CMAKE_CXX_STANDARD 14)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)
set(CMAKE_BUILD_TYPE Release)

add_subdirectory(googlebenchmark)

add_executable(jwbind-benchmark src/jbenchmark.cpp)
target_link_libraries(jwbind-benchmark benchmark::benchmark)