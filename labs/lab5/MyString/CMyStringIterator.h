#pragma once
#include <iterator>

template <typename T>
class CMyStringIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using difference_type = ptrdiff_t;

	using value_type = T;
	using pointer = T*;
	using reference = T&;

	CMyStringIterator()
		: m_ptr()
	{
	}

	CMyStringIterator(pointer ptr)
		: m_ptr(ptr)
	{
	}

	reference operator*() const
	{
		return *m_ptr;
	}

	pointer operator->() const
	{
		return m_ptr;
	}

	CMyStringIterator& operator++()
	{
		++m_ptr;
		return *this;
	}

	CMyStringIterator& operator--()
	{
		--m_ptr;
		return *this;
	}

	CMyStringIterator operator++(int)
	{
		CMyStringIterator temp(m_ptr);
		++m_ptr;
		return temp;
	}

	CMyStringIterator operator--(int)
	{
		CMyStringIterator temp(m_ptr);
		--m_ptr;
		return temp;
	}

	CMyStringIterator& operator+=(difference_type offset)
	{
		m_ptr += offset;
		return *this;
	}

	CMyStringIterator& operator-=(difference_type offset)
	{
		m_ptr -= offset;
		return *this;
	}

	CMyStringIterator operator+(difference_type offset) const
	{
		CMyStringIterator temp(m_ptr);
		return temp += offset;
	}

	CMyStringIterator operator-(difference_type offset) const
	{
		CMyStringIterator temp(m_ptr);
		return temp -= offset;
	}

	difference_type operator-(CMyStringIterator& iterator) const
	{
		return m_ptr - iterator.m_ptr;
	}

	reference operator[](difference_type offset) const
	{
		return *(*this + offset);
	}

	bool operator==(const CMyStringIterator& iterator) const
	{
		return m_ptr == iterator.m_ptr;
	}

	bool operator!=(const CMyStringIterator& iterator) const
	{
		return m_ptr != iterator.m_ptr;
	}

	bool operator<(const CMyStringIterator& iterator) const
	{
		return m_ptr < iterator.m_ptr;
	}

	bool operator>(const CMyStringIterator& iterator) const
	{
		return m_ptr > iterator.m_ptr;
	}

	bool operator<=(const CMyStringIterator& iterator) const
	{
		return m_ptr <= iterator.m_ptr;
	}

	bool operator>=(const CMyStringIterator& iterator) const
	{
		return m_ptr >= iterator.m_ptr;
	}

private:
	pointer m_ptr;
};

// Добавил число + it
template <typename T>
typename CMyStringIterator<T>::CMyStringIterator operator+(typename CMyStringIterator<T>::difference_type offset, CMyStringIterator<T> const& iterator)
{
	return iterator + offset;
};
