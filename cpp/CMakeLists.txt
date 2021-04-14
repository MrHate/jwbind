cmake_minimum_required(VERSION 3.10.2)
project(jwbind-cpp LANGUAGES C CXX VERSION 100)

set(CMAKE_CXX_STANDARD 14)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)
set(CMAKE_BUILD_TYPE Release)

add_subdirectory(binaryen)
add_subdirectory(wparser)
add_subdirectory(gbenchmark)
add_subdirectory(benchmark)
