#include "rotate.hpp"
#include <algorithm>
#include <cstddef>
#include <gtest/gtest.h>
#include <vector>

constexpr std::size_t max_size = 512;

#define MY_TEST(func)                                                                                                  \
	TEST(rotate, func)                                                                                                 \
	{                                                                                                                  \
		for (std::size_t size = 1; size < max_size; ++size)                                                            \
			for (std::size_t shift = 0; shift <= size; ++shift)                                                        \
			{                                                                                                          \
				std::vector<int> vec1(size);                                                                           \
				std::iota(vec1.begin(), vec1.begin(), 0);                                                              \
				auto vec2 = vec1;                                                                                      \
                                                                                                                       \
				std::rotate(vec1.begin(), vec1.begin() + shift, vec1.end());                                           \
				func(vec2.begin(), vec2.begin() + shift, vec2.end());                                                  \
                                                                                                                       \
				EXPECT_TRUE(std::equal(vec1.begin(), vec1.end(), vec2.begin(), vec2.end()));                           \
			}                                                                                                          \
	}

MY_TEST(std_rotate)
MY_TEST(dolphin_rotate_1)
MY_TEST(dolphin_rotate_2)
MY_TEST(three_reverses_rotate)
MY_TEST(gries_mills_rotate_1)
MY_TEST(gries_mills_rotate_2)
MY_TEST(buffer_rotate_1)
MY_TEST(buffer_rotate_2)

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
