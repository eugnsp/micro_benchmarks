#include <algorithm>
#include <benchmark/benchmark.h>
#include <cstddef>
#include <random>
#include <vector>

std::mt19937 gen;

template<class It>
void randomize(It first, It last)
{
	std::iota(first, last, static_cast<std::size_t>(0));
	std::shuffle(first, last, gen);
}

template<class It>
std::size_t count_cycles_0(It first, It last)
{
	std::size_t n_cycles = 0;
	for (auto it = first; it != last; ++it)
	{
		auto it2 = first + *it;
		while (it2 > it)
			it2 = first + *it2;
		if (it2 < it)
			continue;
		++n_cycles;
	}

	return n_cycles;
}

template<class It>
std::size_t count_cycles_1(It first, It last)
{
	const auto n = static_cast<std::size_t>(last - first);
	std::vector<bool> seen(n, false);

	std::size_t n_cycles = 0;
	for (std::size_t i = 0; i < n; ++i)
		if (!seen[i])
		{
			auto it = first + i;
			while (!seen[*it])
			{
				seen[*it] = true;
				it = first + *it;
			}
			++n_cycles;
		}

	return n_cycles;
}

template<class It>
std::size_t count_cycles_2(It first, It last)
{
	const auto n = static_cast<std::size_t>(last - first);

	std::size_t n_swaps = 0;
	for (std::size_t i = 0; i < n; ++i)
		while (first[i] != i)
		{
			std::swap(first[i], first[first[i]]);
			++n_swaps;
		}

	return n - n_swaps;
}

#define MY_BM(func)                                                                                                    \
	void func(benchmark::State& state)                                                                                 \
	{                                                                                                                  \
		std::vector<std::size_t> vec(state.range(0));                                                                  \
		randomize(vec.begin(), vec.end());                                                                             \
		const auto n_cycles = count_cycles_0(vec.begin(), vec.end());                                                  \
		for (auto _ : state)                                                                                           \
		{                                                                                                              \
			state.PauseTiming();                                                                                       \
			auto cpy = vec;                                                                                            \
			state.ResumeTiming();                                                                                      \
                                                                                                                       \
			const auto n = func(cpy.begin(), cpy.end());                                                               \
			if (n != n_cycles)                                                                                         \
				state.SkipWithError("Failed!");                                                                        \
		}                                                                                                              \
	}

MY_BM(count_cycles_0)
BENCHMARK(count_cycles_0)->Range(1L << 8, 1L << 22);

MY_BM(count_cycles_1)
BENCHMARK(count_cycles_1)->Range(1L << 8, 1L << 22);

MY_BM(count_cycles_2)
BENCHMARK(count_cycles_2)->Range(1L << 8, 1L << 22);

BENCHMARK_MAIN();
