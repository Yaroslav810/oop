#pragma once
#include <iostream>
#include <iterator>

template <typename T>
class CStringIterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;

	CStringIterator()
		: m_ptr()
	{
	}

	CStringIterator(pointer ptr)
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

	CStringIterator& operator++()
	{
		if (!m_ptr)
		{
			throw std::logic_error("unavailable iterator");
		}
		m_ptr = m_ptr->GetNext().get();
		return *this;
	}

	CStringIterator& operator--()
	{
		if (!m_ptr)
		{
			throw std::logic_error("unavailable iterator");
		}
		m_ptr = m_ptr->GetPrev().get();
		return *this;
	}

	CStringIterator operator++(int)
	{
		if (!m_ptr)
		{
			throw std::logic_error("unavailable iterator");
		}
		CStringIterator temp(m_ptr);
		m_ptr = m_ptr->GetNext().get();
		return temp;
	}

	CStringIterator operator--(int)
	{
		if (!m_ptr)
		{
			throw std::logic_error("unavailable iterator");
		}
		CStringIterator temp(m_ptr);
		m_ptr = m_ptr->GetPrev().get();
		return temp;
	}

	bool operator==(const CStringIterator& iterator) const
	{
		return m_ptr == iterator.m_ptr;
	}

	bool operator!=(const CStringIterator& iterator) const
	{
		return m_ptr != iterator.m_ptr;
	}

private:
	pointer m_ptr;
};
