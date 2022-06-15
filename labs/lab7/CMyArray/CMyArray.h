#pragma once
#include <iostream>

template <typename T>
class CMyArray
{
public:
	CMyArray() = default;

	explicit CMyArray(size_t size)
		: m_data(new T[size])
		, m_size(size)
	{
	}

private:
	T* m_data = nullptr;
	size_t m_size = 0;
};
