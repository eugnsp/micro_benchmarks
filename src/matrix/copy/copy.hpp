#pragma once
#include "../matrix.hpp"

#include <benchmark/benchmark.h>
#include <mkl.h>

#include <cstddef>

void copy(const Matrix<double>& from, Matrix<double>& to)
{
	for (std::size_t col = 0; col < from.cols(); ++col)
		for (std::size_t row = 0; row < from.rows(); ++row)
			to(row, col) = from(row, col);
}

void copy_transp_contig_write(const Matrix<double>& from, Matrix<double>& to)
{
	for (std::size_t col = 0; col < from.cols(); ++col)
		for (std::size_t row = 0; row < from.rows(); ++row)
			to(row, col) = from(col, row);
}

void copy_transp_contig_read(const Matrix<double>& from, Matrix<double>& to)
{
	for (std::size_t row = 0; row < from.rows(); ++row)
		for (std::size_t col = 0; col < from.cols(); ++col)
			to(row, col) = from(col, row);
}

void copy_transp_mkl(const Matrix<double>& from, Matrix<double>& to)
{
	::mkl_domatcopy('R', 'T', from.rows(), from.cols(), 1., from.data(), from.rows(), to.data(), to.rows());
}