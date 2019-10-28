#include "reverse.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <numeric>
#include <vector>

constexpr std::size_t alignment = 64;
constexpr std::size_t max_size = 32768;

#define MY_TEST(func, T)                                                                           \
	TEST(rotate, func##_##T)                                                                       \
	{                                                                                              \
		for (std::size_t size = 4; size < max_size; size += 4)                                     \
		{                                                                                          \
			auto buff1 = static_cast<T*>(std::aligned_alloc(alignment, size * sizeof(T)));         \
			std::iota(buff1, buff1 + size, 0);                                                     \
			auto buff2 = static_cast<T*>(std::aligned_alloc(alignment, size * sizeof(T)));         \
			std::memcpy(buff2, buff1, size * sizeof(T));                                           \
			std::reverse(buff1, buff1 + size);                                                     \
			func(buff2, buff2 + size);                                                             \
			EXPECT_TRUE(std::equal(buff1, buff1 + size, buff2, buff2 + size));                     \
		}                                                                                          \
	}

MY_TEST(reverse, int)
MY_TEST(block_reverse, int)
MY_TEST(sse_reverse, float)
MY_TEST(sse_reverse, double)

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
