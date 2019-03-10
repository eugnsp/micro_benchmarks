#include "binary_heap.hpp"

#include <benchmark/benchmark.h>
#include <algorithm>
#include <cstddef>
#include <functional>
#include <random>
#include <type_traits>
#include <vector>

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

template<typename T>
void std_quick_sort(benchmark::State &state)	
{
	std::vector<T> vec(state.range(0));
	for (auto _ : state)
	{
		state.PauseTiming();
		randomize(vec);	
		state.ResumeTiming();
		std::sort(vec.begin(), vec.end());
		benchmark::DoNotOptimize(vec);
	}
	state.SetItemsProcessed((int64_t)state.range(0) * state.iterations());
	state.SetComplexityN(state.range(0));
}

BENCHMARK_TEMPLATE(std_quick_sort, int)->Range(1L << 10, 1L << 24)->Complexity(benchmark::oNLogN);

template<typename T>
void std_heap_sort(benchmark::State &state)	
{
	std::vector<T> vec(state.range(0));
	for (auto _ : state)
	{
		state.PauseTiming();
		randomize(vec);	
		state.ResumeTiming();
		std::partial_sort(vec.begin(), vec.end(), vec.end());
		benchmark::DoNotOptimize(vec);
	}
	state.SetItemsProcessed((int64_t)state.range(0) * state.iterations());
	state.SetComplexityN(state.range(0));
}

BENCHMARK_TEMPLATE(std_heap_sort, int)->Range(1L << 10, 1L << 24)->Complexity(benchmark::oNLogN);

template<typename T>
void heap_sort(benchmark::State &state)	
{
	std::vector<T> vec(state.range(0));
	for (auto _ : state)
	{
		state.PauseTiming();
		randomize(vec);	
		state.ResumeTiming();
		Binary_heap<T, std::greater<T>> heap(std::move(vec));
		vec = heap.extract_sorted();
		benchmark::DoNotOptimize(vec);
	}
	state.SetItemsProcessed((int64_t)state.range(0) * state.iterations());
	state.SetComplexityN(state.range(0));
}

BENCHMARK_TEMPLATE(heap_sort, int)->Range(1L << 10, 1L << 24)->Complexity(benchmark::oNLogN);

BENCHMARK_MAIN();
