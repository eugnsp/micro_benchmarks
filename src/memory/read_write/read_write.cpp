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

std::string size_string(std::size_t size)
{
	char size_buf[100];

	if (size < 1'024UL)
		std::snprintf(size_buf, sizeof(size_buf), "%zu B", size);
	else
	{
		if (size < 1'048'576UL)
			std::snprintf(size_buf, sizeof(size_buf), "%.2f KB", size / 1'024.);
		else if (size < 1'073'741'824UL)
			std::snprintf(size_buf, sizeof(size_buf), "%.2f MB", size / 1'048'576.);
		else
			std::snprintf(size_buf, sizeof(size_buf), "%.2f GB", size / 1'073'741'824.);
	}

	return size_buf;
}

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
	BENCHMARK_TEMPLATE(func, std::uint32_t)->RangeMultiplier(2)->Range(1l << 6, 1l << 26);         \
	BENCHMARK_TEMPLATE(func, std::uint64_t)->RangeMultiplier(2)->Range(1l << 6, 1l << 26);         \
	BENCHMARK_TEMPLATE(func, __v32qu      )->RangeMultiplier(2)->Range(1l << 6, 1l << 26);

MY_BENCHMARK(memory_read)
MY_BENCHMARK(memory_write)

BENCHMARK_MAIN();
