#include "reverse.hpp"

#include <benchmark/benchmark.h>

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

#define MY_BENCHMARK(func)                                                                                             \
	template<typename T>                                                                                               \
	void func(benchmark::State& state)                                                                                 \
	{                                                                                                                  \
		std::vector<T> vec(state.range(0));                                                                            \
		std::iota(vec.begin(), vec.end(), T(0));                                                                       \
		for (auto _ : state)                                                                                           \
		{                                                                                                              \
			func(vec.begin(), vec.end());                                                                              \
			benchmark::DoNotOptimize(vec);                                                                             \
		}                                                                                                              \
	}                                                                                                                  \
                                                                                                                       \
	BENCHMARK_TEMPLATE(func, int)->RangeMultiplier(8)->Range(1L << 8, 1L << 26);                                       \
	BENCHMARK_TEMPLATE(func, double)->RangeMultiplier(8)->Range(1L << 8, 1L << 26);

MY_BENCHMARK(std_reverse)
MY_BENCHMARK(reverse_1)
MY_BENCHMARK(reverse_block)

BENCHMARK_MAIN();
