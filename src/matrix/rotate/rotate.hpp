#pragma once
#include "../matrix.hpp"
#include "../matrix_ops.hpp"

#include <benchmark/benchmark.h>

#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

template<typename T>
void rotate(T& v1, T& v2, T& v3, T& v4)
{
	auto tmp = v1;
	v1 = v2;
	v2 = v3;
	v3 = v4;
	v4 = tmp;
}

template<typename T>
void cycle_rotate(Matrix<T>& matrix)
{
	assert(matrix.rows() == matrix.cols());
	const auto n = matrix.rows();
	const auto n_cyclces = n / 2;

	for (std::size_t i = 0, i2 = n - 1; i < n_cyclces; ++i, --i2)
		for (std::size_t j = i, j2 = n - 1 - i; j < n - 1 - i; ++j, --j2)
			rotate(matrix(i, j), matrix(j, i2), matrix(i2, j2), matrix(j2, i));
}

template<typename T>
void flip_transpose_rotate(Matrix<T>& matrix)
{
	transpose(matrix);
	flip_ud(matrix);
}

template<typename T>
void buffer_rotate(Matrix<T>& matrix)
{
	assert(matrix.rows() == matrix.cols());
	const auto n = matrix.rows();

	Matrix<T> tmp(n, n);
	for (std::size_t col = 0; col < n; ++col)
		for (std::size_t row = 0, row2 = n - 1; row < n; ++row, --row2)
			tmp(row2, col) = matrix(col, row);

	matrix.swap(tmp);
}
