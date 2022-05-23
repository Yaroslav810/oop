#pragma once
#include <iostream>
#include <numeric>

class CRational
{
public:
	CRational() = default;
	CRational(int value); // NOLINT(google-explicit-constructor)
	CRational(int numerator, int denominator);

	[[nodiscard]] int GetNumerator() const;
	[[nodiscard]] int GetDenominator() const;
	[[nodiscard]] double ToDouble() const;
	std::pair<int, CRational> ToCompoundFraction() const;

	CRational operator+() const;
	CRational operator-() const;

	CRational operator+=(CRational const& other);
	CRational operator-=(CRational const& other);
	CRational operator*=(CRational const& other);
	CRational operator/=(CRational const& other);

private:
	void NormalizeNumber();

	int m_numerator = 0;
	int m_denominator = 1;
};

CRational operator+(CRational const& number1, CRational const& number2);
CRational operator-(CRational const& number1, CRational const& number2);
CRational operator*(CRational const& number1, CRational const& number2);
CRational operator/(CRational const& number1, CRational const& number2);

bool operator==(CRational const& number1, CRational const& number2);
bool operator!=(CRational const& number1, CRational const& number2);
bool operator<(CRational const& number1, CRational const& number2);
bool operator<=(CRational const& number1, CRational const& number2);
bool operator>(CRational const& number1, CRational const& number2);
bool operator>=(CRational const& number1, CRational const& number2);

std::ostream& operator<<(std::ostream& stream, CRational const& number);
std::istream& operator>>(std::istream& stream, CRational& number);
