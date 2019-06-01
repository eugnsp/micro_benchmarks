#pragma once
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

template<typename T>
class Matrix
{
public:
	Matrix(std::size_t rows, std::size_t cols) : data_(rows * cols), rows_(rows), cols_(cols)
	{}

	Matrix(std::size_t rows, std::size_t cols, const T& value) : data_(rows * cols, value), rows_(rows), cols_(cols)
	{}

	T& operator()(std::size_t row, std::size_t col)
	{
		assert(row < rows_ && col < cols_);
		return data_[row + col * rows_];
	}

	const T& operator()(std::size_t row, std::size_t col) const
	{
		assert(row < rows_ && col < cols_);
		return data_[row + col * rows_];
	}

	std::size_t rows() const
	{
		return rows_;
	}

	std::size_t cols() const
	{
		return cols_;
	}

	std::size_t size() const
	{
		return rows_ * cols_;
	}

	auto& vec()
	{
		return data_;
	}

	auto data()
	{
		return data_.data();
	}

	auto data() const
	{
		return data_.data();
	}

	void swap(Matrix& other)
	{
		std::swap(data_, other.data_);
		std::swap(rows_, other.rows_);
		std::swap(cols_, other.cols_);
	}

	bool operator==(const Matrix& other) const
	{
		return rows_ == other.rows_ && cols_ == other.cols_ && data_ == other.data_;
	}

private:
	std::vector<T> data_;
	std::size_t rows_;
	std::size_t cols_;
};
