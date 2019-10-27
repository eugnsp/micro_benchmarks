#include "rotate.hpp"
#include "../matrix.hpp"
#include "../matrix_ops.hpp"

#include <benchmark/benchmark.h>

#include <cmath>
#include <cstddef>
#include <string>

using T = double;

static void custom_arguments(benchmark::internal::Benchmark* b)
{
	for (int i = 16; i <= 4096; i *= 2)
		for (int j = i; j < 2 * i; j += std::max(4, i / 8))
		{
			b->Args({j - 1});
			b->Args({j});
			b->Args({j + 1});
		}
}

#define MY_BENCHMARK(func)                                                                         \
	void func(benchmark::State& state)                                                             \
	{                                                                                              \
		const std::size_t n = state.range(0);                                                      \
		Matrix<T> mat(n, n);                                                                       \
		for (auto _ : state)                                                                       \
		{                                                                                          \
			func(mat);                                                                             \
			benchmark::DoNotOptimize(mat.data());                                                  \
		}                                                                                          \
		state.SetItemsProcessed(state.iterations() * mat.size());                                  \
		state.SetLabel(std::to_string(mat.size() * sizeof(T)));                                    \
	}                                                                                              \
                                                                                                   \
	BENCHMARK(func)->Apply(custom_arguments);

MY_BENCHMARK(transpose)
MY_BENCHMARK(flip_ud)
MY_BENCHMARK(flip_transpose_rotate)
MY_BENCHMARK(cycle_rotate)
MY_BENCHMARK(buffer_rotate)

BENCHMARK_MAIN();
