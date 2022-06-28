#pragma once
#include <iterator>

template <typename T>
class CMyArrayIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using difference_type = ptrdiff_t;
	using value_type = T;
	using reference = T&;
	using pointer = T*;

	CMyArrayIterator(T* ptr)
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

	CMyArrayIterator& operator++()
	{
		m_ptr++;
		return *this;
	}

	CMyArrayIterator& operator--()
	{
		m_ptr--;
		return *this;
	}

	CMyArrayIterator operator++(int)
	{
		CMyArrayIterator temp(*this);
		++*this;
		return temp;
	}

	CMyArrayIterator operator--(int)
	{
		CMyArrayIterator temp(*this);
		--*this;
		return temp;
	}

	CMyArrayIterator& operator+=(const difference_type offset)
	{
		m_ptr += offset;
		return *this;
	}

	CMyArrayIterator& operator-=(const difference_type offset)
	{
		m_ptr -= offset;
		return *this;
	}

	CMyArrayIterator operator+(const difference_type& offset) const
	{
		return CMyArrayIterator(m_ptr + offset);
	}

	difference_type operator-(const CMyArrayIterator& it) const
	{
		return m_ptr - it.m_ptr;
	}

	CMyArrayIterator operator-(const difference_type& offset) const
	{
		return CMyArrayIterator(m_ptr - offset);
	}

	reference operator[](const difference_type& offset) const
	{
		return *(*this + offset);
	}

	bool operator==(const CMyArrayIterator& it) const
	{
		return m_ptr == it.m_ptr;
	}

	bool operator!=(const CMyArrayIterator& it) const
	{
		return m_ptr != it.m_ptr;
	}

	bool operator<(const CMyArrayIterator& it) const
	{
		return m_ptr < it.m_ptr;
	}

	bool operator>(const CMyArrayIterator& it) const
	{
		return m_ptr > it.m_ptr;
	}

	bool operator<=(const CMyArrayIterator& it) const
	{
		return m_ptr <= it.m_ptr;
	}

	bool operator>=(const CMyArrayIterator& it) const
	{
		return m_ptr >= it.m_ptr;
	}

	operator CMyArrayIterator<const T>() const
	{
		return CMyArrayIterator<const T>(m_ptr);
	}

private:
	T* m_ptr;
};
