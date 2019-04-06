#include "rotate.hpp"
#include <benchmark/benchmark.h>
#include <algorithm>
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

#define MY_BM(func)                                                                                \
	template<typename T>                                                                           \
	void func(benchmark::State& state)                                                             \
	{                                                                                              \
		std::vector<T> vec(state.range(0));                                                        \
		std::iota(vec.begin(), vec.end(), T(0));                                                   \
		for (auto _ : state)                                                                       \
		{                                                                                          \
			const auto n_first = random_it(vec.begin(), vec.end());                                \
			func(vec.begin(), n_first, vec.end());                                                 \
			benchmark::DoNotOptimize(vec);                                                         \
		}                                                                                          \
		state.SetComplexityN(state.range(0));                                                      \
	}

MY_BM(std_rotate)
BENCHMARK_TEMPLATE(std_rotate, int)->Range(1L << 5, 1L << 27)->Complexity(benchmark::oN);

MY_BM(dolphin_rotate_1)
BENCHMARK_TEMPLATE(dolphin_rotate_1, int)->Range(1L << 5, 1L << 27)->Complexity(benchmark::oN);

MY_BM(dolphin_rotate_2)
BENCHMARK_TEMPLATE(dolphin_rotate_2, int)->Range(1L << 5, 1L << 27)->Complexity(benchmark::oN);

MY_BM(three_reverses_rotate)
BENCHMARK_TEMPLATE(three_reverses_rotate, int)->Range(1L << 5, 1L << 27)->Complexity(benchmark::oN);

MY_BM(gries_mills_rotate_1)
BENCHMARK_TEMPLATE(gries_mills_rotate_1, int)->Range(1L << 5, 1L << 27)->Complexity(benchmark::oN);

MY_BM(gries_mills_rotate_2)
BENCHMARK_TEMPLATE(gries_mills_rotate_2, int)->Range(1L << 5, 1L << 27)->Complexity(benchmark::oN);

MY_BM(buffer_rotate_1)
BENCHMARK_TEMPLATE(buffer_rotate_1, int)->Range(1L << 5, 1L << 27)->Complexity(benchmark::oN);

MY_BM(buffer_rotate_2)
BENCHMARK_TEMPLATE(buffer_rotate_2, int)->Range(1L << 5, 1L << 27)->Complexity(benchmark::oN);

BENCHMARK_MAIN();
