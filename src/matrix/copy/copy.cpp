#include "copy.hpp"
#include "../matrix.hpp"
#include "../matrix_ops.hpp"

#include <benchmark/benchmark.h>

#include <cstddef>
#include <string>

static void custom_arguments(benchmark::internal::Benchmark* b)
{
	for (int i = 16; i <= (1 << 12); i *= 2)
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
		Matrix<double> from(n, n);                                                                 \
		Matrix<double> to(n, n);                                                                   \
		for (auto _ : state)                                                                       \
		{                                                                                          \
			func(from, to);                                                                        \
			benchmark::DoNotOptimize(to.data());                                                   \
		}                                                                                          \
		state.SetItemsProcessed(state.iterations() * from.size());                                 \
		state.SetLabel(std::to_string(from.size() * sizeof(double)));                              \
	}                                                                                              \
                                                                                                   \
	BENCHMARK(func)->Apply(custom_arguments);

MY_BENCHMARK(copy)
MY_BENCHMARK(copy_transp_contig_write)
MY_BENCHMARK(copy_transp_contig_read)
MY_BENCHMARK(copy_transp_mkl)

BENCHMARK_MAIN();
