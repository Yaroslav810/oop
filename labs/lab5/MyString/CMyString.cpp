#include "CMyString.h"

CMyString::CMyString()
	: m_data(new char[1])
	, m_length(0)
{
	m_data[0] = '\0';
}

CMyString::CMyString(const char* pString)
	: m_data(new char[std::strlen(pString) + 1])
	, m_length(std::strlen(pString))
{
}

CMyString::CMyString(const char* pString, size_t length)
{
}
