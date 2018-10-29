#pragma once
#include <cassert>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <utility>
#include <vector>

template<typename T, class Comparator = std::less<T>>
class Binary_heap
{
public:
	Binary_heap() = default;
	
	Binary_heap(std::initializer_list<T> list) :
		heap_(list.begin(), list.end())
	{
		build_heap();
	}

	Binary_heap(const std::vector<T>& values) :
		heap_(values)
	{
		build_heap();
	}

	Binary_heap(std::vector<T>&& values) :
		heap_(std::move(values))
	{
		build_heap();
	}

	std::size_t size() const
	{
		return heap_.size();
	}

	bool is_empty() const
	{
		return heap_.empty();
	}

	T& min()
	{ 
		assert(!is_empty());
		return heap_.front();
	}

	const T& min() const
	{ 
		assert(!is_empty());
		return heap_.front();
	}

	void remove_min()
	{
		assert(!is_empty());

		heap_.front() = std::move(heap_.back());
		heap_.pop_back();
		sift_down(0);
	}

	std::vector<T> extract_sorted()
	{
		using std::swap;
		
		for (auto s = size() - 1; s > 0; --s)
		{
			swap(heap_.front(), heap_[s]);
			sift_down(0, s);
		}

		return std::move(heap_);
	}

	void insert(const T& value)
	{
		heap_.push_back(value);
		sift_up(size() - 1);
	}

	void insert(T&& value)
	{
		heap_.push_back(std::move(value));
		sift_up(size() - 1);
	}
	
	auto& heap() const
	{
		return heap_;
	}

private:
	static std::size_t parent_idx(std::size_t index)
	{
		assert(index > 0);
		return (index - 1) / 2;
	}

 	static std::size_t left_child_idx(std::size_t index)
 	{ 
		return 2 * index + 1;
	}

	void build_heap()
	{
		if (size() < 2)
			return;

		const auto first_leaf_idx = size() / 2;		
		auto s = first_leaf_idx;

		do
			sift_down(--s);
		while (s > 0);
	}

	void sift_up(std::size_t index)
	{
		assert(index < size());
		
		auto value = std::move(heap_[index]);
		while (index > 0)
		{
			const auto parent = parent_idx(index);
			if (!cmp_(value, heap_[parent]))
				break;

			heap_[index] = std::move(heap_[parent]);
			index = parent;
		}

		heap_[index] = std::move(value);
	}

	void sift_down(std::size_t index)
	{	
		sift_down(index, size());
	}

	// Does nothing if (index) >= (size)
	void sift_down(std::size_t index, std::size_t size)
	{
		assert(size <= this->size());

		auto value = std::move(heap_[index]);		
		while (true)
		{
			auto child = left_child_idx(index);
			if (child >= size)
				break;

			if (child + 1 < size && cmp_(heap_[child + 1], heap_[child]))
				++child;
			if (!cmp_(heap_[child], value))
				break;

			heap_[index] = std::move(heap_[child]);
			index = child;
		}

		heap_[index] = std::move(value);
	}

private:
	std::vector<T> heap_;
	Comparator cmp_;
};
