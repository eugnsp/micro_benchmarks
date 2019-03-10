#include <benchmark/benchmark.h>
#include <algorithm>
#include <cstddef>
#include <random>
#include <vector>

// Problem: for a 2D boolean matrix with sorted rows,
// find the first row with the maximum number of 1s

template<class Containter>
void randomize(Containter& c, std::size_t n, int filling)
{
	std::mt19937 gen;
	std::bernoulli_distribution dis(filling / 100.);
	std::generate(c.begin(), c.end(), [&]() { return dis(gen); });

	for (std::size_t i = 0; i < n; ++i)
		std::sort(c.begin() + i * n, c.begin() + (i + 1) * n);
}

template<typename T>
std::size_t row_with_max_number_of_1s_v0(const std::vector<T>& mat, std::size_t rows)
{
	std::size_t max_row = 0;
	std::size_t max_n = 0;

	const auto cols = mat.size() / rows;
	for (std::size_t row = 0; row < rows; ++row)
	{
		const auto first = mat.begin() + row * cols;
		const auto last = mat.begin() + (row + 1) * cols;
		const auto pos = std::lower_bound(first, last, 1);
		const auto n = static_cast<std::size_t>(last - pos);
		if (n > max_n)
		{
			max_n = n;
			max_row = row;
		}
	}

	return max_row;
}

template<typename T>
std::size_t row_with_max_number_of_1s_v1(const std::vector<T>& mat, std::size_t rows)
{
	std::size_t max_row = 0;
	std::size_t max_n = 0;

	const auto cols = mat.size() / rows;
	for (std::size_t row = 0; row < rows; ++row)
	{
		const auto first = mat.begin() + row * cols;
		if (first[cols - max_n - 1] == 0)
			continue;

		const auto last = mat.begin() + (row + 1) * cols;
		const auto pos = std::lower_bound(first, last - max_n, 1);
		const auto n = static_cast<std::size_t>(last - pos);
		if (n > max_n)
		{
			if (n == cols)
				return row;
			max_n = n;
			max_row = row;
		}
	}

	return max_row;
}

template<typename T>
std::size_t row_with_max_number_of_1s_v2(const std::vector<T>& mat, std::size_t rows)
{
	const auto cols = mat.size() / rows;

	std::size_t max_row = 0;
	std::size_t max_n = 0;

	for (std::size_t row = 0; row < rows; ++row)
	{
		const auto first = mat.begin() + row * cols;
		if (first[cols - max_n - 1] == 0)
			continue;

		for (auto it = first + cols - max_n; it != first && *(it - 1) == 1; --it)
			++max_n;

		if (max_n == cols)
			return row;
		max_row = row;
	}

	return max_row;
}

static void CustomArguments(benchmark::internal::Benchmark* b)
{
	for (int i = (1 << 9); i <= (1 << 13); i <<= 1)
	{
		b->Args({i, 1});
		b->Args({i, 50});
		b->Args({i, 99});
	}
}

#define MY_BM(func)                                                                                \
	void func(benchmark::State& state)                                                             \
	{                                                                                              \
		const auto n = state.range(0);                                                             \
		std::vector<int> vec(n * n);                                                               \
		randomize(vec, n, state.range(1));                                                         \
		for (auto _ : state)                                                                       \
		{                                                                                          \
			auto row = row_with_max_number_of_1s_##func(vec, n);                                   \
			benchmark::DoNotOptimize(row);                                                         \
		}                                                                                          \
		state.SetComplexityN(state.range(0));                                                      \
	}

MY_BM(v0)
BENCHMARK(v0)->Apply(CustomArguments);

MY_BM(v1)
BENCHMARK(v1)->Apply(CustomArguments);

MY_BM(v2)
BENCHMARK(v2)->Apply(CustomArguments);

BENCHMARK_MAIN();
