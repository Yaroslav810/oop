#include "CRational.h"

CRational::CRational(int value)
	: m_numerator(value)
	, m_denominator(1)
{
}

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Zero denominator");
	}

	NormalizeNumber();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return static_cast<double>(GetNumerator()) / GetDenominator();
}

CRational CRational::operator+() const
{
	return *this;
}

CRational CRational::operator-() const
{
	return { -m_numerator, m_denominator };
}

CRational CRational::operator+=(const CRational& other)
{
	auto lcm = std::lcm(GetDenominator(), other.GetDenominator());
	auto numerator1 = GetNumerator() * (lcm / GetDenominator());
	auto numerator2 = other.GetNumerator() * (lcm / other.GetDenominator());
	m_numerator = numerator1 + numerator2;
	m_denominator = lcm;
	NormalizeNumber();

	return *this;
}

CRational CRational::operator-=(const CRational& other)
{
	return *this += -other;
}

CRational CRational::operator*=(const CRational& other)
{
	m_numerator *= other.GetNumerator();
	m_denominator *= other.GetDenominator();
	NormalizeNumber();

	return *this;
}

CRational CRational::operator/=(const CRational& other)
{
	return *this *= {other.GetDenominator(), other.GetNumerator()};
}

void CRational::NormalizeNumber()
{
	if (m_denominator < 0)
	{
		m_numerator *= -1;
		m_denominator *= -1;
	}

	if (auto gcd = std::gcd(m_numerator, m_denominator);
		gcd != 1 && gcd != 0)
	{
		m_numerator /= gcd;
		m_denominator /= gcd;
	}
}

CRational operator+(CRational const& number1, CRational const& number2)
{
	return CRational(number1.GetNumerator(), number1.GetDenominator()) += number2;
}

CRational operator-(CRational const& number1, CRational const& number2)
{
	return CRational(number1.GetNumerator(), number1.GetDenominator()) -= number2;
}

CRational operator*(CRational const& number1, CRational const& number2)
{
	return CRational(number1.GetNumerator(), number1.GetDenominator()) *= number2;
}

CRational operator/(CRational const& number1, CRational const& number2)
{
	return CRational(number1.GetNumerator(), number1.GetDenominator()) /= number2;
}

bool operator==(CRational const& number1, CRational const& number2)
{
	return number1.GetNumerator() == number2.GetNumerator() && number1.GetDenominator() == number2.GetDenominator();
}

bool operator!=(CRational const& number1, CRational const& number2)
{
	return !(number1 == number2);
}

bool operator<(CRational const& number1, CRational const& number2)
{
	auto lcm = std::lcm(number1.GetDenominator(), number2.GetDenominator());
	auto numerator1 = number1.GetNumerator() * (lcm / number1.GetDenominator());
	auto numerator2 = number2.GetNumerator() * (lcm / number2.GetDenominator());
	return numerator1 < numerator2;
}

bool operator<=(CRational const& number1, CRational const& number2)
{
	return number1 < number2 || number1 == number2;
}

bool operator>(CRational const& number1, CRational const& number2)
{
	return !(number1 <= number2);
}

bool operator>=(CRational const& number1, CRational const& number2)
{
	return !(number1 < number2);
}

std::ostream& operator<<(std::ostream& stream, CRational const& number)
{
	return stream << number.GetNumerator() << '/' << number.GetDenominator();
}

std::istream& operator>>(std::istream& stream, CRational& number)
{
	int numerator;
	int denominator;
	if ((stream >> numerator) && (stream.get() == '/') && (stream >> denominator))
	{
		number = CRational(numerator, denominator);
	}
	else
	{
		stream.setstate(std::ios_base::failbit | stream.rdstate());
	}

	return stream;
}
