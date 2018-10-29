cmake_minimum_required(VERSION 3.5)
project(merge_sort)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic -O3 -m64 -DNDEBUG)

cmake_policy(SET CMP0003 OLD)

add_library(google-benchmark STATIC IMPORTED)
add_library(intel-tbb UNKNOWN IMPORTED)

set(LIB_PATH "/home/es/lib")

set_target_properties(google-benchmark PROPERTIES
	IMPORTED_LOCATION "${LIB_PATH}/google/benchmark/build/src/libbenchmark.a"
	INTERFACE_INCLUDE_DIRECTORIES "${LIB_PATH}/google/benchmark/include")

set_target_properties(intel-tbb PROPERTIES
	IMPORTED_LOCATION "${LIB_PATH}/intel/tbb/tbb2018_20180822oss/lib/intel64/gcc4.7/libtbb.so"
	INTERFACE_INCLUDE_DIRECTORIES "${LIB_PATH}/intel/tbb/tbb2018_20180822oss/include")

add_executable(merge_sort merge_sort.cpp)
target_link_libraries(merge_sort google-benchmark intel-tbb pthread)
