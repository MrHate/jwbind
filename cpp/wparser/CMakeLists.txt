cmake_minimum_required(VERSION 3.10.2)
project(wparser LANGUAGES C CXX VERSION 100)

set(CMAKE_CXX_STANDARD 14)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(EXEC_NAME wparser)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out )
add_executable(${EXEC_NAME} src/wparser.cpp)

target_link_libraries(${EXEC_NAME} PUBLIC binaryen)
target_link_libraries(${EXEC_NAME} PRIVATE Threads::Threads)
target_include_directories(${EXEC_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/binaryen/src)
