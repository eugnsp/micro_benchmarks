#include <benchmark/benchmark.h>

#include <cstddef>
#include <numeric>
#include <vector>

template<typename T>
void func(benchmark::State& state)
{
	std::vector<T> vec(state.range(0), 0);
	for (auto _ : state)
	{
		//const auto s = std::accumulate(vec.begin(), vec.end(), 0);
		std::fill(vec.begin(), vec.end(), 0);
		benchmark::DoNotOptimize(vec);
	}
	state.SetComplexityN(state.range(0));
}

BENCHMARK_TEMPLATE(func, bool)->RangeMultiplier(2)->Range(1L << 5, 1L << 25);
BENCHMARK_TEMPLATE(func, char)->RangeMultiplier(2)->Range(1L << 5, 1L << 25);
BENCHMARK_TEMPLATE(func, int)->RangeMultiplier(2)->Range(1L << 5, 1L << 25);

BENCHMARK_MAIN();
