cmake_minimum_required (VERSION 3.7)
project (micro_benchmarks)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wno-comment -Wno-switch -m64 -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-Wextra -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
add_subdirectory(external/benchmark)
add_subdirectory(external/googletest/googletest)

set(TBB_BUILD_TESTS OFF CACHE BOOL "Build TBB tests and enable testing infrastructure" FORCE)
add_subdirectory(external/tbb)

add_executable(heap_sort src/heap_sort/heap_sort.cpp)
target_link_libraries(heap_sort benchmark)

add_executable(merge_sort src/merge_sort/merge_sort.cpp)
target_link_libraries(merge_sort benchmark tbb pthread)

add_executable(matrix_row_max_1s src/matrix_row_max_1s/matrix_row_max_1s.cpp)
target_link_libraries(matrix_row_max_1s benchmark)
