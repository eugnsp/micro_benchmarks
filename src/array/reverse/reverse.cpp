#include "reverse.hpp"

#include <benchmark/benchmark.h>

#include <immintrin.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

static void custom_arguments(benchmark::internal::Benchmark* b)
{
	for (auto i = (1ll << 11); i <= (1ll << 30); i *= 2)
		for (auto j = i; j < 2 * i; j += i / 2)
			b->Args({j});
}

constexpr std::size_t alignment = 64;

#define MY_BENCHMARK(func)                                                                         \
	template<typename T>                                                                           \
	void func(benchmark::State& state)                                                             \
	{                                                                                              \
		const std::size_t n = state.range(0) / sizeof(T);                                          \
		auto buff = static_cast<T*>(std::aligned_alloc(alignment, n * sizeof(T)));                 \
		for (auto _ : state)                                                                       \
		{                                                                                          \
			func(buff, buff + n);                                                                  \
			benchmark::DoNotOptimize(*buff);                                                       \
		}                                                                                          \
		std::free(buff);                                                                           \
		state.SetBytesProcessed(state.iterations() * n * sizeof(T));                               \
		state.SetLabel(std::to_string(n * sizeof(T)));                                             \
	}                                                                                              \
                                                                                                   \
	BENCHMARK_TEMPLATE(func, float)->Apply(custom_arguments);                                      \
	BENCHMARK_TEMPLATE(func, double)->Apply(custom_arguments);

// BENCHMARK_TEMPLATE(func, std::uint8_t)->Apply(custom_arguments);                               \
	// BENCHMARK_TEMPLATE(func, std::uint32_t)->Apply(custom_arguments);                              \
	// BENCHMARK_TEMPLATE(func, std::uint64_t)->Apply(custom_arguments);                              \
	// BENCHMARK_TEMPLATE(func, __v32qu)->Apply(custom_arguments);

MY_BENCHMARK(reverse)
MY_BENCHMARK(block_reverse)
MY_BENCHMARK(sse_reverse)

BENCHMARK_MAIN();
