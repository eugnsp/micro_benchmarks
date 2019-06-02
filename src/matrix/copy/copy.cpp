#include "copy.hpp"
#include "../matrix.hpp"
#include "../matrix_ops.hpp"

#include <benchmark/benchmark.h>

#include <cstddef>

constexpr auto no_false_sharing = 1u;

#define MY_BENCHMARK(func)                                                                                             \
	void func(benchmark::State& state)                                                                                 \
	{                                                                                                                  \
		const std::size_t n = state.range(0) + no_false_sharing;                                                       \
		Matrix<double> from(n, n);                                                                                     \
		Matrix<double> to(n, n);                                                                                       \
		for (auto _ : state)                                                                                           \
		{                                                                                                              \
			func(from, to);                                                                                            \
			benchmark::DoNotOptimize(to.data());                                                                       \
		}                                                                                                              \
		state.SetBytesProcessed(state.iterations() * from.size() * sizeof(double));                                    \
	}                                                                                                                  \
                                                                                                                       \
	BENCHMARK(func)->RangeMultiplier(2)->Range(1l << 5, 1l << 14);

MY_BENCHMARK(copy)
MY_BENCHMARK(copy_tr_write_contig)
MY_BENCHMARK(copy_tr_read_contig)
MY_BENCHMARK(copy_tr_mkl)

BENCHMARK_MAIN();
