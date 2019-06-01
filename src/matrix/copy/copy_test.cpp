#include "../matrix.hpp"
#include "copy.hpp"

#include <gtest/gtest.h>

#include <cstddef>
#include <numeric>

template<typename T>
bool is_transposed_equal(const Matrix<T>& mat1, const Matrix<T>& mat2)
{
	if (mat1.rows() != mat2.rows() || mat1.cols() != mat2.cols())
		return false;

	for (std::size_t row = 0; row < mat1.rows(); ++row)
		for (std::size_t col = 0; col < mat1.cols(); ++col)
			if (mat1(row, col) != mat2(col, row))
				return false;

	return true;
}

constexpr std::size_t max_size = 128;

#define MY_TEST(func)                                                                                                  \
	TEST(rotate, func)                                                                                                 \
	{                                                                                                                  \
		for (std::size_t n = 1; n < max_size; ++n)                                                                     \
		{                                                                                                              \
			Matrix<double> mat1(n, n);                                                                                 \
			std::iota(mat1.data(), mat1.data() + mat1.size(), 0);                                                      \
			Matrix<double> mat2(n, n);                                                                                 \
			func(mat1, mat2);                                                                                          \
			EXPECT_TRUE(is_transposed_equal(mat1, mat2));                                                              \
		}                                                                                                              \
	}

MY_TEST(copy_tr_write_contig)
MY_TEST(copy_tr_read_contig)
MY_TEST(copy_tr_mkl)

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
