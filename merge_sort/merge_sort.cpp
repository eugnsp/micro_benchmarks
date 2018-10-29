#include "serial.hpp"
#include "parallel.hpp"
#include <benchmark/benchmark.h>
#include <algorithm>
#include <random>
#include <type_traits>
#include <vector>

#if __has_include(<execution>)
#define HAS_STD_EXECUTION
#endif

#ifdef HAS_STD_EXECUTION
#include <execution>
#endif

template<class Containter, typename... Params>
void randomize(Containter& c, Params... params)
{
	using T = typename Containter::value_type;
	
	std::mt19937 gen;
	std::conditional_t<std::is_integral_v<T>,
		std::uniform_int_distribution<T>,
		std::uniform_real_distribution<T>> dis{static_cast<T>(params)...};
	std::generate(c.begin(), c.end(), [&]() { return dis(gen); });
}

template<class Rand_access_it>
void std_stable_sort_seq(Rand_access_it first, Rand_access_it last)
{
	std::stable_sort(first, last);
}

#ifdef HAS_STD_EXECUTION
template<class Rand_access_it>
void std_stable_sort_par(Rand_access_it first, Rand_access_it last)
{
	std::stable_sort(std::execution::par, first, last);
}
#endif

#define MY_BM(func)															\
template<typename T>														\
void func(benchmark::State &state)											\
{																			\
	std::vector<T> vec(state.range(0));										\
	for (auto _ : state)													\
	{																		\
		state.PauseTiming();												\
		randomize(vec);														\
		state.ResumeTiming();												\
		func(vec.begin(), vec.end());										\
		benchmark::DoNotOptimize(vec);										\
	}																		\
	state.SetItemsProcessed((int64_t)state.range(0) * state.iterations());	\
	state.SetComplexityN(state.range(0));									\
}

MY_BM(std_stable_sort_seq)
BENCHMARK_TEMPLATE(std_stable_sort_seq, int)->Range(1L << 10, 1L << 24)->Complexity();

#ifdef HAS_STD_EXECUTION
MY_BM(std_stable_sort_par)
BENCHMARK_TEMPLATE(std_stable_sort_par, int)->Range(1L << 10, 1L << 24)->Complexity();
#endif

MY_BM(std_serial_merge_sort)
BENCHMARK_TEMPLATE(std_serial_merge_sort, int)->Range(1L << 10, 1L << 24)->Complexity();

MY_BM(serial_merge_sort)
BENCHMARK_TEMPLATE(serial_merge_sort, int)->Range(1L << 10, 1L << 24)->Complexity();

MY_BM(serial_merge_sort_buff)
BENCHMARK_TEMPLATE(serial_merge_sort_buff, int)->Range(1L << 10, 1L << 24)->Complexity();

MY_BM(tbb_merge_sort)
BENCHMARK_TEMPLATE(tbb_merge_sort, int)->Range(1L << 10, 1L << 24)->Complexity();

BENCHMARK_MAIN();
