#pragma once
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <vector>
#include <array>

template<class It>
void std_reverse(const It first, const It last)
{
	std::reverse(first, last);
}

template<class It>
void reverse_1(It first, It last)
{
	while (first < last)
	{
		std::iter_swap(first, last - 1);
		++first;
		--last;
	}
}

template<class It>
void reverse_block(It first, It last)
{
	using T = typename std::iterator_traits<It>::value_type;

	constexpr std::size_t block_size_bytes = 128;
	constexpr std::size_t block_size = block_size_bytes / sizeof(T);
	std::array<T, block_size> buff;

	while (first + block_size < last - block_size)
	{
		std::copy(last - block_size, last, buff.begin());
		std::reverse_copy(first, first + block_size, last - block_size);
		std::reverse_copy(buff.begin(), buff.end(), first);

		first += block_size;
		last -= block_size;
	}

	if (first < last)
		std::reverse(first, last);
}

