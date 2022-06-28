#include "CMyStringIterator.h"
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);

	CMyString(CMyString const& other);
	CMyString(CMyString&& other) noexcept;
	CMyString(std::string const& stlString);

	[[nodiscard]] size_t GetLength() const;
	[[nodiscard]] const char* GetStringData() const;
	[[nodiscard]] static const char* GetDefaultString();

	[[nodiscard]] CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	CMyString& operator=(const CMyString& other);
	CMyString& operator=(CMyString&& other) noexcept;
	CMyString& operator+=(const CMyString& other);
	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	using iterator = CMyStringIterator<char>;
	using const_iterator = CMyStringIterator<const char>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	iterator begin();
	iterator end();
	[[nodiscard]] const_iterator begin() const;
	[[nodiscard]] const_iterator end() const;
	reverse_iterator rbegin();
	reverse_iterator rend();
	[[nodiscard]] const_reverse_iterator rbegin() const;
	[[nodiscard]] const_reverse_iterator rend() const;

private:
	constexpr static const char defaultString[] = { '\0' };
	std::unique_ptr<char[]> m_data;
	size_t m_length;
};

CMyString operator+(CMyString lhs, CMyString const& rhs);
bool operator==(CMyString const& lhs, CMyString const& rhs);
bool operator!=(CMyString const& lhs, CMyString const& rhs);
bool operator<(CMyString const& lhs, CMyString const& rhs);
bool operator>(CMyString const& lhs, CMyString const& rhs);
bool operator<=(CMyString const& lhs, CMyString const& rhs);
bool operator>=(CMyString const& lhs, CMyString const& rhs);

std::ostream& operator<<(std::ostream& stream, const CMyString& string);
std::istream& operator>>(std::istream& stream, const CMyString& string);
