#include "binary_heap.hpp"

#include <benchmark/benchmark.h>
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <random>
#include <vector>

std::mt19937 gen;

template<class It>
void randomize(It first, It last)
{
	using T = typename std::iterator_traits<It>::value_type;

	std::uniform_int_distribution<T> dis;
	std::generate(first, last, [&]() { return dis(gen); });
}

template<typename T>
void std_quick_sort(benchmark::State& state)
{
	std::vector<T> vec(state.range(0));
	for (auto _ : state)
	{
		state.PauseTiming();
		randomize(vec.begin(), vec.end());
		state.ResumeTiming();
		std::sort(vec.begin(), vec.end());
		state.PauseTiming();
		const bool f = std::is_sorted(vec.begin(), vec.end());
		if (!f)
			state.SkipWithError("Failed!");
		state.ResumeTiming();
	}
	state.SetItemsProcessed((int64_t)state.range(0) * state.iterations());
	state.SetComplexityN(state.range(0));
}

BENCHMARK_TEMPLATE(std_quick_sort, int)->Range(1L << 10, 1L << 24)->Complexity(benchmark::oNLogN);

template<typename T>
void std_heap_sort(benchmark::State& state)
{
	std::vector<T> vec(state.range(0));
	for (auto _ : state)
	{
		state.PauseTiming();
		randomize(vec.begin(), vec.end());
		state.ResumeTiming();
		std::partial_sort(vec.begin(), vec.end(), vec.end());
		state.PauseTiming();
		const bool f = std::is_sorted(vec.begin(), vec.end());
		if (!f)
			state.SkipWithError("Failed!");
		state.ResumeTiming();
	}
	state.SetItemsProcessed((int64_t)state.range(0) * state.iterations());
	state.SetComplexityN(state.range(0));
}

BENCHMARK_TEMPLATE(std_heap_sort, int)->Range(1L << 10, 1L << 24)->Complexity(benchmark::oNLogN);

template<typename T>
void heap_sort(benchmark::State& state)
{
	std::vector<T> vec(state.range(0));
	for (auto _ : state)
	{
		state.PauseTiming();
		randomize(vec.begin(), vec.end());
		state.ResumeTiming();
		Binary_heap<T, std::greater<T>> heap(std::move(vec));
		vec = heap.extract_sorted();
		state.PauseTiming();
		const bool f = std::is_sorted(vec.begin(), vec.end());
		if (!f)
			state.SkipWithError("Failed!");
		state.ResumeTiming();
	}
	state.SetItemsProcessed((int64_t)state.range(0) * state.iterations());
	state.SetComplexityN(state.range(0));
}

BENCHMARK_TEMPLATE(heap_sort, int)->Range(1L << 10, 1L << 24)->Complexity(benchmark::oNLogN);

BENCHMARK_MAIN();
