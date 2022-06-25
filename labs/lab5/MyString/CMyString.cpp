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
	if (std::addressof(other) != this)
	{
		std::swap(m_data, other.m_data);
		std::swap(m_length, other.m_length);
	}
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
	return m_data.get();
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)
	{
		return {};
	}

	size_t len = length;
	if (length > m_length - start)
	{
		len = m_length - start;
	}

	return { m_data.get() + start, len };
}

void CMyString::Clear()
{
	m_data.reset();
	m_data = std::make_unique<char[]>(1);
	m_data[0] = '\0';
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

const char CMyString::operator[](size_t index) const
{
	if (index > m_length)
	{
		throw std::out_of_range("index out of range");
	}

	return m_data[index];
}

char& CMyString::operator[](size_t index)
{
	if (index > m_length)
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
	auto minLength = std::min(lhs.GetLength(), rhs.GetLength());
	auto result = std::memcmp(lhs.GetStringData(), rhs.GetStringData(), minLength);

	if (result != 0)
	{
		return false;
	}

	if (lhs.GetLength() == rhs.GetLength())
	{
		return false;
	}

	return rhs.GetLength() > minLength;
}

bool operator>(CMyString const& lhs, CMyString const& rhs)
{
	return !(lhs < rhs) && !(lhs == rhs);
}

bool operator<=(CMyString const& lhs, CMyString const& rhs)
{
	return !(lhs > rhs);
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
