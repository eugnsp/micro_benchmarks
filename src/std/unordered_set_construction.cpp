#include <benchmark/benchmark.h>

#include <algorithm>
#include <random>
#include <unordered_set>
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
void from_range(benchmark::State& state)
{
	std::vector<T> vec(state.range(0));
	randomize(vec.begin(), vec.end());
	for (auto _ : state)
	{
		std::unordered_set<int> set(vec.begin(), vec.end());
		benchmark::DoNotOptimize(set);
	}
}

template<typename T>
void from_inserts(benchmark::State& state)
{
	std::vector<T> vec(state.range(0));
	randomize(vec.begin(), vec.end());
	for (auto _ : state)
	{
		std::unordered_set<int> set;
		for (auto x : vec)
			set.insert(x);
		benchmark::DoNotOptimize(set);
	}
}

BENCHMARK_TEMPLATE(from_range, int)->Range(1L << 8, 1L << 20);
BENCHMARK_TEMPLATE(from_inserts, int)->Range(1L << 8, 1L << 20);

BENCHMARK_MAIN();
