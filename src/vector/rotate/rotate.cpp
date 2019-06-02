#include "rotate.hpp"
#include <algorithm>
#include <benchmark/benchmark.h>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

std::mt19937 gen;

template<class It>
It random_it(const It first, const It last)
{
	std::uniform_int_distribution dis(first - first, last - first);
	return first + dis(gen);
}

#define MY_BENCHMARK(func)                                                                                             \
	template<typename T>                                                                                               \
	void func(benchmark::State& state)                                                                                 \
	{                                                                                                                  \
		std::vector<T> vec(state.range(0));                                                                            \
		std::iota(vec.begin(), vec.end(), T(0));                                                                       \
		for (auto _ : state)                                                                                           \
		{                                                                                                              \
			const auto n_first = random_it(vec.begin(), vec.end());                                                    \
			func(vec.begin(), n_first, vec.end());                                                                     \
			benchmark::DoNotOptimize(vec);                                                                             \
		}                                                                                                              \
		state.SetComplexityN(state.range(0));                                                                          \
	}                                                                                                                  \
                                                                                                                       \
	BENCHMARK_TEMPLATE(func, int)->RangeMultiplier(4)->Range(1L << 6, 1L << 26);

MY_BENCHMARK(std_rotate)
MY_BENCHMARK(dolphin_rotate_1)
MY_BENCHMARK(dolphin_rotate_2)
MY_BENCHMARK(three_reverses_rotate)
MY_BENCHMARK(gries_mills_rotate_1)
MY_BENCHMARK(gries_mills_rotate_2)
MY_BENCHMARK(buffer_rotate_1)
MY_BENCHMARK(buffer_rotate_2)

BENCHMARK_MAIN();
