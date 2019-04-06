#include "../matrix.hpp"
#include "../matrix_ops.hpp"
#include "rotate.hpp"
#include <benchmark/benchmark.h>
#include <cstddef>

using T = int;
constexpr auto no_false_sharing = 1u;

#define MY_BENCHMARK(func)                                                                         \
	void func(benchmark::State& state)                                                             \
	{                                                                                              \
		const std::size_t n = state.range(0) + no_false_sharing;                                   \
		Matrix<T> mat(n, n);                                                                       \
		for (auto _ : state)                                                                       \
		{                                                                                          \
			func(mat);                                                                             \
			benchmark::DoNotOptimize(mat.data());                                                  \
		}                                                                                          \
		state.SetBytesProcessed(state.iterations() * mat.size() * sizeof(T));                      \
		state.SetComplexityN(n);                                                                   \
	}                                                                                              \
                                                                                                   \
	BENCHMARK(func)->RangeMultiplier(2)->Range(1l << 3, 1l << 13)->Complexity(benchmark::oNSquared);

MY_BENCHMARK(transpose)
MY_BENCHMARK(flip_ud)
MY_BENCHMARK(flip_transpose_rotate)
MY_BENCHMARK(cycle_rotate)
MY_BENCHMARK(buffer_rotate)

BENCHMARK_MAIN();
