#include <benchmark/benchmark.h>

#include <immintrin.h>

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#define REPEAT4(x) x x x x
#define REPEAT16(x) REPEAT4(x) REPEAT4(x) REPEAT4(x) REPEAT4(x)
#define REPEAT64(x) REPEAT16(x) REPEAT16(x) REPEAT16(x) REPEAT16(x)
#define REPEAT(x) REPEAT64(x)

constexpr std::size_t n_reps = 0 REPEAT(+1);
constexpr std::size_t alignment = 64;

template<typename T>
void memory_read(T* const buff, std::size_t size)
{
	assert(size % n_reps == 0);

	[[maybe_unused]] T sink;

	const auto last = buff + size;
	for (volatile T* it = buff; it != last;)
	{
		REPEAT(sink = *it++;)
	}
}

template<typename T>
void memory_write(T* const buff, std::size_t size)
{
	assert(size % n_reps == 0);

	T source;
	std::memset(&source, 0, sizeof(T));

	const auto last = buff + size;
	for (volatile T* it = buff; it != last;)
	{
		REPEAT(*it++ = source;)
	}
}

static void custom_arguments(benchmark::internal::Benchmark* b)
{
	for (int i = 64; i <= (1 << 25); i *= 2)
		for (int j = i; j < 2 * i; j += i / 2)
			b->Args({j});
}

#define MY_BENCHMARK(func)                                                                         \
	template<typename T>                                                                           \
	void func(benchmark::State& state)                                                             \
	{                                                                                              \
		const std::size_t n = n_reps * (state.range(0) / sizeof(T));                               \
		auto buff = static_cast<T*>(std::aligned_alloc(alignment, n * sizeof(T)));                 \
		for (auto _ : state)                                                                       \
			func(buff, n);                                                                         \
		std::free(buff);                                                                           \
		state.SetBytesProcessed(state.iterations() * n * sizeof(T));                               \
		state.SetLabel(std::to_string(n * sizeof(T)));                                             \
	}                                                                                              \
                                                                                                   \
	BENCHMARK_TEMPLATE(func, std::uint32_t)->Apply(custom_arguments);                              \
	BENCHMARK_TEMPLATE(func, std::uint64_t)->Apply(custom_arguments);                              \
	BENCHMARK_TEMPLATE(func, __v32qu)->Apply(custom_arguments);

MY_BENCHMARK(memory_read)
MY_BENCHMARK(memory_write)

BENCHMARK_MAIN();
