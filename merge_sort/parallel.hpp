#pragma once
#include "serial.hpp"
#include <tbb/tbb.h>
#include <algorithm>

#define PARALLEL_MERGE_LIMIT 500
//#define NO_TBB_PARALLEL

template<class Rand_access_it>
void tbb_merge(Rand_access_it first1, Rand_access_it last1,
	Rand_access_it first2, Rand_access_it last2, Rand_access_it dest)
{
	assert(first1 <= last1 && first2 <= last2);

	if ((last1 - first1) + (last2 - first2) <= PARALLEL_MERGE_LIMIT)
	{
		serial_merge(first1, last1, first2, last2, dest);
		return;
	}

	Rand_access_it mid1, mid2;
	if (last1 - first1 > last2 - first2)
	{
		mid1 = first1 + (last1 - first1) / 2;
		mid2 = std::lower_bound(first2, last2, *mid1);
	}
	else
	{
		mid2 = first2 + (last2 - first2) / 2;
		mid1 = std::upper_bound(first1, last1, *mid2);
	}

	const auto dest_mid = dest + (mid1 - first1) + (mid2 - first2);
	
#ifdef NO_TBB_PARALLEL
	tbb_merge(first1, mid1, first2, mid2, dest);
	tbb_merge(mid1, last1, mid2, last2, dest_mid);
#else
	tbb::parallel_invoke(
		[=]() { tbb_merge(first1, mid1, first2, mid2, dest); },
		[=]() { tbb_merge(mid1, last1, mid2, last2, dest_mid); });	
#endif
}

template<class Rand_access_it>
void tbb_merge(Rand_access_it first, Rand_access_it mid, Rand_access_it last,
	Rand_access_it dest)
{
	tbb_merge(first, mid, mid, last, dest);
}

template<class Rand_access_it>
void tbb_merge_sort_impl(Rand_access_it first, Rand_access_it last, Rand_access_it dest, bool in_place)
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

	#ifdef NO_TBB_PARALLEL
		tbb_merge_sort_impl(first, mid, dest, !in_place);
		tbb_merge_sort_impl(mid, last, dest_mid, !in_place);
	#else
		tbb::parallel_invoke(
			[=]() { tbb_merge_sort_impl(first, mid, dest, !in_place); },
			[=]() { tbb_merge_sort_impl(mid, last, dest_mid, !in_place); });
	#endif

		if (in_place)
			tbb_merge(dest, dest_mid, dest_end, first);
		else
			tbb_merge(first, mid, last, dest);
	}
}

template<class Rand_access_it>
void tbb_merge_sort(Rand_access_it first, Rand_access_it last)
{
	using T = typename std::iterator_traits<Rand_access_it>::value_type;
	std::vector<T> buf(last - first);
	tbb_merge_sort_impl(first, last, buf.begin(), true);
}