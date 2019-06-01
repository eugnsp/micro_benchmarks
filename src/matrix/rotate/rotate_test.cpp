#include "../matrix.hpp"
#include "../matrix_ops.hpp"
#include "rotate.hpp"

#include <gtest/gtest.h>

#include <cassert>
#include <cstddef>
#include <numeric>

template<typename T>
bool is_rotated(const Matrix<T>& mat1, const Matrix<T>& mat2)
{
	const auto n = mat1.rows();

	for (std::size_t row = 0; row < n; ++row)
		for (std::size_t col = 0; col < n; ++col)
			if (mat1(row, col) != mat2(n - 1 - col, row))
				return false;

	return true;
}

using T = int;
constexpr std::size_t max_size = 32;

#define MY_TEST(func)                                                                                                  \
	TEST(rotate, func)                                                                                                 \
	{                                                                                                                  \
		for (std::size_t n = 1; n < max_size; ++n)                                                                     \
		{                                                                                                              \
			Matrix<T> mat(n, n);                                                                                       \
			std::iota(mat.data(), mat.data() + mat.size(), 0);                                                         \
			auto mat1 = mat;                                                                                           \
			func(mat1);                                                                                                \
			EXPECT_TRUE(is_rotated(mat, mat1));                                                                        \
		}                                                                                                              \
	}

MY_TEST(cycle_rotate)
MY_TEST(flip_transpose_rotate)
MY_TEST(buffer_rotate)

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
