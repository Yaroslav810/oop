#pragma once
#include "CMyArrayIterator.h"
#include <iostream>
#include <memory>

template <typename T>
class CMyArray
{
public:
	CMyArray()
		: m_data(nullptr)
		, m_size(0)
	{
	}

	CMyArray(size_t size)
		: m_data(std::make_unique<T[]>(size))
		, m_size(size)
	{
	}

	CMyArray(const CMyArray& other)
	{
		try
		{
			std::unique_ptr<T[]> newData = std::make_unique<T[]>(other.m_size);
			std::copy(std::begin(other), std::end(other), newData.get());
			m_data = std::move(newData);
			m_size = other.m_size;
		}
		catch (...)
		{
			Clear();
			throw;
		}
	}

	CMyArray(CMyArray&& other) noexcept
		: m_data(nullptr)
		, m_size(0)
	{
		std::swap(m_data, other.m_data);
		std::swap(m_size, other.m_size);
	}

	[[nodiscard]] size_t GetSize() const
	{
		return m_size;
	}

	void Push(T const& item)
	{
		Resize(m_size + 1);
		m_data[m_size - 1] = item;
	}

	void Clear()
	{
		m_data.reset();
		m_size = 0;
	}

	void Resize(size_t newSize)
	{
		std::unique_ptr<T[]> newData = std::make_unique<T[]>(newSize);

		if (newSize >= m_size)
		{
			std::copy(m_data.get(), m_data.get() + m_size, newData.get());
		}
		else
		{
			std::copy(m_data.get(), m_data.get() + newSize, newData.get());
		}

		m_data = std::move(newData);
		m_size = newSize;
	}

	CMyArray& operator=(const CMyArray& other)
	{
		if (std::addressof(other) != this)
		{
			CMyArray copy(other);
			std::swap(m_data, copy.m_data);
			std::swap(m_size, copy.m_size);
		}
		return *this;
	}

	CMyArray& operator=(CMyArray&& other) noexcept
	{
		if (std::addressof(other) != this)
		{
			m_size = 0;
			m_data = nullptr;
			std::swap(m_data, other.m_data);
			std::swap(m_size, other.m_size);
		}
		return *this;
	}

	const T& operator[](size_t index) const
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Out of bounds index");
		}
		return m_data[index];
	}

	T& operator[](size_t index)
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Out of bounds index");
		}
		return m_data[index];
	}

	using iterator = CMyArrayIterator<T>;
	using const_iterator = CMyArrayIterator<const T>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	iterator begin()
	{
		return iterator(m_data.get());
	}

	iterator end()
	{
		return iterator(m_data.get() + m_size);
	}

	const_iterator begin() const
	{
		return const_iterator(m_data.get());
	}

	const_iterator end() const
	{
		return const_iterator(m_data.get() + m_size);
	}

	reverse_iterator rbegin()
	{
		return std::make_reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return std::make_reverse_iterator(begin());
	}

	const_reverse_iterator rbegin() const
	{
		return std::make_reverse_iterator(end());
	}

	const_reverse_iterator rend() const
	{
		return std::make_reverse_iterator(begin());
	}

private:
	std::unique_ptr<T[]> m_data;
	size_t m_size;
};
