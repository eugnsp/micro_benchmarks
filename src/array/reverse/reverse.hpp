#pragma once
#include <immintrin.h>

#include <array>
#include <cstddef>
#include <utility>

#define REPEAT4(x) x x x x
#define REPEAT16(x) REPEAT4(x) REPEAT4(x) REPEAT4(x) REPEAT4(x)
#define REPEAT64(x) REPEAT16(x) REPEAT16(x) REPEAT16(x) REPEAT16(x)
#define REPEAT(x) REPEAT64(x)

inline constexpr std::size_t n_reps = 0 REPEAT(+1);

template<typename T>
void reverse(T* first, T* last)
{
	while (first < last)
		std::swap(*first++, *--last);
}

template<typename T>
void copy(const T* source, std::size_t size, T* dest)
{
	while (size-- > 0)
		*dest++ = *source++;
}

template<typename T>
void reverse_copy(const T* source, std::size_t size, T* dest)
{
	while (size-- > 0)
		*--dest = *source++;
}

template<typename T>
void block_reverse(T* first, T* last)
{
	constexpr std::size_t block_size_bytes = 128;
	constexpr std::size_t block_size = block_size_bytes / sizeof(T);
	std::array<T, block_size> buff;

	while (first + block_size <= last - block_size)
	{
		copy(last - block_size, block_size, buff.data());
		reverse_copy(first, block_size, last);
		first += block_size;
		reverse_copy(buff.data(), block_size, first);
		last -= block_size;
	}

	if (first < last)
		reverse(first, last);
}

void sse_reverse(float* first, float* last)
{
	constexpr auto block_size = sizeof(__m128) / sizeof(float);
	while (first + block_size * n_reps <= last - block_size * n_reps)
	{
		REPEAT(
		{
			last -= block_size;
			auto v1 = _mm_loadr_ps(first);
			auto v2 = _mm_loadr_ps(last);
			_mm_store_ps(last, v1);
			_mm_store_ps(first, v2);
			first += block_size;
		})
	}

	if (first < last)
		reverse(first, last);
}

void sse_reverse(double* first, double* last)
{
	constexpr auto block_size = sizeof(__m128d) / sizeof(double);
	while (first + block_size * n_reps <= last - block_size * n_reps)
	{
		REPEAT(
		{
			last -= block_size;
			auto v1 = _mm_loadr_pd(first);
			auto v2 = _mm_loadr_pd(last);
			_mm_store_pd(last, v1);
			_mm_store_pd(first, v2);
			first += block_size;
		})
	}

	if (first < last)
		reverse(first, last);
}
