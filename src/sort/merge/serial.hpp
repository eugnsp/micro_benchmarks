#pragma once
#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

#define INSERTION_SORT_LIMIT 100

template<class Rand_access_it>
void serial_insertion_sort(Rand_access_it first, Rand_access_it last)
{
	assert(first <= last);
	if (last - first <= 1)
		return;

	// Invariant: the range [first, end) is sorted
	auto end = std::next(first);
	while (end != last)
	{
		auto end_element = *end;

		auto pos = end;
		while (pos > first && *std::prev(pos) > end_element)
		{
			*pos = *std::prev(pos);
			--pos;
		}

		*pos = end_element;
		++end;
	}
}

template<class Rand_access_it>
void serial_merge_in_place(Rand_access_it first, Rand_access_it mid, Rand_access_it last)
{
	assert(first <= mid && mid <= last);

	using T = typename std::iterator_traits<Rand_access_it>::value_type;
	std::vector<T> tmp;

	const auto size = static_cast<std::size_t>(last - first);
	tmp.reserve(size);

	auto p1 = first;
	auto p2 = mid;
	while (p1 != mid && p2 != last)
	{
		auto& p = (*p1 <= *p2) ? p1 : p2;
		tmp.push_back(*p++);
	}

	tmp.insert(tmp.end(), p1, mid);
	tmp.insert(tmp.end(), p2, last);

	assert(tmp.size() == size);
	std::copy(tmp.begin(), tmp.end(), first);
}

template<class Rand_access_it>
void serial_merge(
	Rand_access_it first1, Rand_access_it last1, Rand_access_it first2, Rand_access_it last2, Rand_access_it dest)
{
	assert(first1 <= last1 && first2 <= last2);

	auto p1 = first1;
	auto p2 = first2;
	while (p1 != last1 && p2 != last2)
	{
		auto& p = (*p1 <= *p2) ? p1 : p2;
		*dest++ = *p++;
	}

	std::copy(p1, last1, dest);
	std::copy(p2, last2, dest);
}

template<class Rand_access_it>
void serial_merge(Rand_access_it first, Rand_access_it mid, Rand_access_it last, Rand_access_it dest)
{
	serial_merge(first, mid, mid, last, dest);
}

template<class Rand_access_it>
void serial_merge_sort(Rand_access_it first, Rand_access_it last)
{
	assert(first <= last);
	if (last - first <= INSERTION_SORT_LIMIT)
		serial_insertion_sort(first, last);
	else
	{
		const auto mid = first + (last - first) / 2;
		serial_merge_sort(first, mid);
		serial_merge_sort(mid, last);
		serial_merge_in_place(first, mid, last);
	}
}

template<class Rand_access_it>
void serial_merge_sort_buff_impl(Rand_access_it first, Rand_access_it last, Rand_access_it dest, bool in_place)
{
	assert(first <= last);
	if (last - first <= INSERTION_SORT_LIMIT)
	{
		serial_insertion_sort(first, last);
		if (!in_place)
			std::copy(first, last, dest);
	}
	else
	{
		const auto mid = first + (last - first) / 2;
		const auto dest_mid = dest + (mid - first);
		const auto dest_end = dest + (last - first);

		serial_merge_sort_buff_impl(first, mid, dest, !in_place);
		serial_merge_sort_buff_impl(mid, last, dest_mid, !in_place);

		if (in_place)
			serial_merge(dest, dest_mid, dest_end, first);
		else
			serial_merge(first, mid, last, dest);
	}
}

template<class Rand_access_it>
void serial_merge_sort_buff(Rand_access_it first, Rand_access_it last)
{
	using T = typename std::iterator_traits<Rand_access_it>::value_type;
	std::vector<T> buff(last - first);
	serial_merge_sort_buff_impl(first, last, buff.begin(), true);
}

template<class Rand_access_it>
void std_serial_merge_sort(Rand_access_it first, Rand_access_it last)
{
	if (last - first <= 1)
		return;

	const auto middle = first + (last - first) / 2;
	std_serial_merge_sort(first, middle);
	std_serial_merge_sort(middle, last);
	std::inplace_merge(first, middle, last);
}
