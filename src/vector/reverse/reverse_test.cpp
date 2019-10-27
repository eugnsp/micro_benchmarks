#include "reverse.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <vector>

constexpr std::size_t max_size = 512;

#define MY_TEST(func)                                                                                                  \
	TEST(rotate, func)                                                                                                 \
	{                                                                                                                  \
		for (std::size_t size = 1; size < max_size; ++size)                                                            \
		{                                                                                                              \
			std::vector<int> vec1(size);                                                                               \
			std::iota(vec1.begin(), vec1.begin(), 0);                                                                  \
			auto vec2 = vec1;                                                                                          \
                                                                                                                       \
			std::reverse(vec1.begin(), vec1.end());                                                                    \
			func(vec2.begin(), vec2.end());                                                                            \
                                                                                                                       \
			EXPECT_TRUE(std::equal(vec1.begin(), vec1.end(), vec2.begin(), vec2.end()));                               \
		}                                                                                                              \
	}

MY_TEST(reverse_1)
MY_TEST(reverse_block)

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
