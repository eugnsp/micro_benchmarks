#pragma once
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <vector>

template<class It>
void std_rotate(const It first, const It n_first, const It last)
{
	std::rotate(first, n_first, last);
}

template<class It>
void dolphin_rotate_1(const It first, const It n_first, const It last)
{
	if (n_first == first || n_first == last)
		return;

	const auto n_last = first + (last - n_first);
	const auto k = n_first - first;
	const auto nmk = last - n_first;

	const auto n_cycles = std::gcd(n_first - first, last - n_first);
	for (std::ptrdiff_t i = 0; i < n_cycles; ++i)
	{
		auto it = first + i;
		auto tmp = std::move(*it);
		const auto start = it;

		while (true)
		{
			const auto next = (it < n_last) ? it + k : it - nmk;
			if (next == start)
				break;

			*it = std::move(*next);
			it = next;
		}

		*it = std::move(tmp);
	}
}

template<class It>
void dolphin_rotate_2(const It first, const It n_first, const It last)
{
	const auto shift = n_first - first;
	auto count = std::gcd(shift, last - first);

	if (count < last - first)
		for (; 0 < count; --count)
		{
			const auto hole = first + count;
			auto next = hole;
			auto next1 = next + shift == last ? first : next + shift;
			do
			{
				std::iter_swap(next, next1);
				next = next1;
				if (shift < last - next1)
					next1 = next1 + shift;
				else
					next1 = first + (shift - (last - next1));
			} while (next1 != hole);
		}
}

template<class It>
std::pair<It, It> swap_ranges_bounded(It first1, const It last1, It first2, const It last2)
{
	while (first1 != last1 && first2 != last2)
		std::iter_swap(first1++, first2++);
	return {first1, first2};
}

template<class It>
void gries_mills_rotate_1(It first, It n_first, const It last)
{
	if (n_first == first || n_first == last)
		return;

	while (true)
	{
		const auto p = swap_ranges_bounded(first, n_first, n_first, last);
		if (p.first == n_first)
		{
			if (p.second == last)
				return;

			first = n_first;
			n_first = p.second;
		}
		else
			first = p.first;
	}
}

template<class It>
void gries_mills_rotate_2(It first, It n_first, const It last)
{
	if (n_first == first || n_first == last)
		return;

	auto it = n_first;
	do
	{
		std::iter_swap(first++, it++);
		if (first == n_first)
			n_first = it;
	} while (it != last);

	it = n_first;
	while (it != last)
	{
		std::iter_swap(first++, it++);
		if (first == n_first)
			n_first = it;
		else if (it == last)
			it = n_first;
	}
}

template<class It>
void three_reverses_rotate(const It first, const It n_first, const It last)
{
	std::reverse(first, n_first);
	std::reverse(n_first, last);
	std::reverse(first, last);
}

template<class It>
void buffer_rotate_1(const It first, const It n_first, const It last)
{
	std::vector buff(n_first, last);
	std::copy_backward(first, n_first, last);
	std::copy(buff.begin(), buff.end(), first);
}

template<class It>
void buffer_rotate_2(const It first, const It n_first, const It last)
{
	std::vector buff(first, n_first);
	auto n_last = std::copy(n_first, last, first);
	std::copy(buff.begin(), buff.end(), n_last);
}
