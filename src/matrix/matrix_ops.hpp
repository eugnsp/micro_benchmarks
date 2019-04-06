#pragma once
#include "matrix.hpp"
#include <cassert>
#include <cstddef>
#include <utility>

template<typename T>
void transpose(Matrix<T>& matrix)
{
	assert(matrix.rows() == matrix.cols());
	const auto n = matrix.rows();

	for (std::size_t col = 0; col < n; ++col)
		for (std::size_t row = 0; row < col; ++row)
			std::swap(matrix(row, col), matrix(col, row));
}

template<typename T>
void flip_ud(Matrix<T>& matrix)
{
	for (std::size_t col = 0; col < matrix.cols(); ++col)
		for (std::size_t row = 0, row2 = matrix.rows() - 1; row < row2; ++row, --row2)
			std::swap(matrix(row, col), matrix(row2, col));
}
