#include "CMyString.h"

CMyString::CMyString()
	: m_data(std::make_unique<char[]>(1))
	, m_length(0)
{
	m_data[0] = '\0';
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, pString != nullptr ? std::strlen(pString) : 0)
{
}

CMyString::CMyString(const char* pString, size_t length)
	: m_data(std::make_unique<char[]>(pString == nullptr ? 1 : length + 1))
	, m_length(pString == nullptr ? 0 : length)
{
	std::memcpy(m_data.get(), pString, m_length);
	m_data[m_length] = '\0';
}

CMyString::CMyString(const CMyString& other)
	: CMyString(other.GetStringData(), other.GetLength())
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_data(nullptr)
	, m_length(0)
{
	// Была лишняя проверка
	std::swap(m_data, other.m_data);
	std::swap(m_length, other.m_length);
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.c_str(), stlString.size())
{
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	// Выводить default string при nullptr
	if (!m_data)
	{
		return defaultString;
	}
	return m_data.get();
}

const char* CMyString::GetDefaultString()
{
	return defaultString;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	// Избавиться от лишней переменной len
	if (start >= m_length)
	{
		return {};
	}
	// Тут nullptr создаваться не будет
	return { m_data.get() + start, std::min(length, m_length - start) };
}

void CMyString::Clear()
{
	// std::make_unique<char[]>(1) может выбросить исключение
	auto data = std::make_unique<char[]>(1);
	data[0] = '\0';
	m_data.reset();
	m_data = std::move(data);
	m_length = 0;
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (std::addressof(other) != this)
	{
		CMyString copy(other);
		std::swap(m_data, copy.m_data);
		std::swap(m_length, copy.m_length);
	}

	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (std::addressof(other) != this)
	{
		m_data = nullptr;
		m_length = 0;
		std::swap(m_data, other.m_data);
		std::swap(m_length, other.m_length);
	}

	return *this;
}

CMyString& CMyString::operator+=(const CMyString& other)
{
	size_t commonLength = m_length + other.m_length;
	auto data = std::make_unique<char[]>(commonLength + 1);

	std::memcpy(data.get(), m_data.get(), m_length);
	std::memcpy(data.get() + m_length, other.m_data.get(), commonLength - m_length);
	data[commonLength] = '\0';

	m_data = std::move(data);
	m_length = commonLength;

	return *this;
}

// Сделал const char&
const char& CMyString::operator[](size_t index) const
{
	// Поменял c > на >=
	if (index >= m_length)
	{
		throw std::out_of_range("index out of range");
	}

	return m_data[index];
}

char& CMyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw std::out_of_range("index out of range");
	}

	return m_data[index];
}

CMyString operator+(CMyString lhs, CMyString const& rhs)
{
	return lhs += rhs;
}

bool operator==(CMyString const& lhs, CMyString const& rhs)
{
	if (lhs.GetLength() != rhs.GetLength())
	{
		return false;
	}

	return std::memcmp(lhs.GetStringData(), rhs.GetStringData(), lhs.GetLength()) == 0;
}

bool operator!=(CMyString const& lhs, CMyString const& rhs)
{
	return !(lhs == rhs);
}

bool operator<(CMyString const& lhs, CMyString const& rhs)
{
	// Упростил код
	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

bool operator>(CMyString const& lhs, CMyString const& rhs)
{
	// Упростил код
	return rhs < lhs;
}

bool operator<=(CMyString const& lhs, CMyString const& rhs)
{
	return !(rhs < lhs);
}

bool operator>=(CMyString const& lhs, CMyString const& rhs)
{
	return !(lhs < rhs);
}

std::ostream& operator<<(std::ostream& output, CMyString const& string)
{
	auto const str = string.GetStringData();
	for (size_t i = 0; i < string.GetLength(); ++i)
	{
		output << str[i];
	}
	return output;
}

CMyString::iterator CMyString::begin()
{
	return { m_data.get() };
}

CMyString::iterator CMyString::end()
{
	return { m_data.get() + m_length };
}

CMyString::const_iterator CMyString::begin() const
{
	return { m_data.get() };
}

CMyString::const_iterator CMyString::end() const
{
	return { m_data.get() + m_length };
}

CMyString::reverse_iterator CMyString::rbegin()
{
	return std::make_reverse_iterator(end());
}

CMyString::reverse_iterator CMyString::rend()
{
	return std::make_reverse_iterator(begin());
}

CMyString::const_reverse_iterator CMyString::rbegin() const
{
	return std::make_reverse_iterator(end());
}

CMyString::const_reverse_iterator CMyString::rend() const
{
	return std::make_reverse_iterator(begin());
}
