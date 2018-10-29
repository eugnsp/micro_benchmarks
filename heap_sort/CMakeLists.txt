cmake_minimum_required(VERSION 3.5)
project(heap_sort)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic -O3 -m64 -DNDEBUG)

cmake_policy(SET CMP0003 OLD)

add_library(google-benchmark STATIC IMPORTED)

set(LIB_PATH "/home/es/lib")

set_target_properties(google-benchmark PROPERTIES
	IMPORTED_LOCATION "${LIB_PATH}/google/benchmark/build/src/libbenchmark.a"
	INTERFACE_INCLUDE_DIRECTORIES "${LIB_PATH}/google/benchmark/include")

add_executable(heap_sort heap_sort.cpp)
target_link_libraries(heap_sort google-benchmark pthread)
