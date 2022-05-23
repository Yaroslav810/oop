#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../CRational.h"

TEST_CASE("Initialization of a rational number")
{
	SECTION("Default constructor")
	{
		CRational rational;
		REQUIRE(rational.GetNumerator() == 0);
		REQUIRE(rational.GetDenominator() == 1);
	}

	SECTION("Constructor with numerator")
	{
		SECTION("Constructor with numerator 0")
		{
			CRational rational(0);
			REQUIRE(rational.GetNumerator() == 0);
			REQUIRE(rational.GetDenominator() == 1);
		}

		SECTION("Constructor with numerator 20")
		{
			CRational rational(20);
			REQUIRE(rational.GetNumerator() == 20);
			REQUIRE(rational.GetDenominator() == 1);
		}

		SECTION("Constructor with numerator -20")
		{
			CRational rational(-20);
			REQUIRE(rational.GetNumerator() == -20);
			REQUIRE(rational.GetDenominator() == 1);
		}
	}

	SECTION("Full Constructor")
	{
		SECTION("Constructor with numerator = 10 and denominator = 20. Waiting = 1/2")
		{
			CRational rational(10, 20);
			REQUIRE(rational.GetNumerator() == 1);
			REQUIRE(rational.GetDenominator() == 2);
		}

		SECTION("Constructor with numerator = 0 and denominator = 1. Waiting = 0/1")
		{
			CRational rational(0, 1);
			REQUIRE(rational.GetNumerator() == 0);
			REQUIRE(rational.GetDenominator() == 1);
		}

		SECTION("Constructor with numerator = 9 and denominator = 13. Waiting = 9/13")
		{
			CRational rational(9, 13);
			REQUIRE(rational.GetNumerator() == 9);
			REQUIRE(rational.GetDenominator() == 13);
		}

		SECTION("Constructor with numerator = 5 and denominator = 15. Waiting = 1/3")
		{
			CRational rational(5, 15);
			REQUIRE(rational.GetNumerator() == 1);
			REQUIRE(rational.GetDenominator() == 3);
		}

		SECTION("Constructor with numerator = -5 and denominator = 15. Waiting = -1/3")
		{
			CRational rational(-5, 15);
			REQUIRE(rational.GetNumerator() == -1);
			REQUIRE(rational.GetDenominator() == 3);
		}

		SECTION("Constructor with numerator = 5 and denominator = -15. Waiting = -1/3")
		{
			CRational rational(5, -15);
			REQUIRE(rational.GetNumerator() == -1);
			REQUIRE(rational.GetDenominator() == 3);
		}
	}

	SECTION("Creation error")
	{
		REQUIRE_THROWS_AS(CRational(0, 0), std::invalid_argument);
		REQUIRE_THROWS_AS(CRational(1, 0), std::invalid_argument);
		REQUIRE_THROWS_AS(CRational(-1, 0), std::invalid_argument);
	}
}

TEST_CASE("Converting a rational number to a double")
{
	SECTION("Conversion 0")
	{
		CRational rational;
		REQUIRE(rational.ToDouble() == 0);
	}

	SECTION("Conversion 5/1")
	{
		CRational rational(5);
		REQUIRE(rational.ToDouble() == 5);
	}

	SECTION("Conversion 2/4")
	{
		CRational rational(2, 4);
		REQUIRE(rational.ToDouble() == 0.5);
	}

	SECTION("Conversion -1/2")
	{
		CRational rational(-1, 2);
		REQUIRE(rational.ToDouble() == -0.5);
	}
}

TEST_CASE("Unary plus operation")
{
	SECTION("Taking the unary plus from 0, with expectation 0/1")
	{
		CRational rational;
		auto result = +rational;
		REQUIRE(result.GetNumerator() == 0);
		REQUIRE(result.GetDenominator() == 1);
	}

	SECTION("Taking the unary plus from 1/2, with expectation 1/2")
	{
		CRational rational(1, 2);
		auto result = +rational;
		REQUIRE(result.GetNumerator() == 1);
		REQUIRE(result.GetDenominator() == 2);
	}

	SECTION("Taking the unary plus from -1/2, with expectation -1/2")
	{
		CRational rational(-1, 2);
		auto result = +rational;
		REQUIRE(result.GetNumerator() == -1);
		REQUIRE(result.GetDenominator() == 2);
	}
}

TEST_CASE("Unary minus operation")
{
	SECTION("Taking the unary minus from 0, with expectation -0/1")
	{
		CRational rational;
		auto result = -rational;
		REQUIRE(result.GetNumerator() == -0);
		REQUIRE(result.GetDenominator() == 1);
	}

	SECTION("Taking the unary minus from 1/2, with expectation -1/2")
	{
		CRational rational(1, 2);
		auto result = -rational;
		REQUIRE(result.GetNumerator() == -1);
		REQUIRE(result.GetDenominator() == 2);
	}

	SECTION("Taking the unary minus from -1/2, with expectation 1/2")
	{
		CRational rational(-1, 2);
		auto result = -rational;
		REQUIRE(result.GetNumerator() == 1);
		REQUIRE(result.GetDenominator() == 2);
	}
}

TEST_CASE("Summation of numbers")
{
	SECTION("Addition of 1/2 and 1/6 with expectation of 2/3")
	{
		CRational rational1(1, 2);
		CRational rational2(1, 6);
		auto result = rational1 + rational2;
		REQUIRE(result.GetNumerator() == 2);
		REQUIRE(result.GetDenominator() == 3);
	}

	SECTION("Addition of 1/2 and 1 with expectation of 3/2")
	{
		CRational rational(1, 2);
		auto result = rational + 1;
		REQUIRE(result.GetNumerator() == 3);
		REQUIRE(result.GetDenominator() == 2);
	}

	SECTION("Addition of 1 and 1/2 with expectation of 3/2")
	{
		CRational rational(1, 2);
		auto result = 1 + rational;
		REQUIRE(result.GetNumerator() == 3);
		REQUIRE(result.GetDenominator() == 2);
	}

	SECTION("Addition of -1/2 and -1/2 with expectation of -1")
	{
		CRational rational1(-1, 2);
		CRational rational2(-1, 2);
		auto result = rational1 + rational2;
		REQUIRE(result.GetNumerator() == -1);
		REQUIRE(result.GetDenominator() == 1);
	}

	SECTION("Addition of -1/2 and 1/2 with expectation of 0")
	{
		CRational rational1(-1, 2);
		CRational rational2(1, 2);
		auto result = rational1 + rational2;
		REQUIRE(result.GetNumerator() == 0);
		REQUIRE(result.GetDenominator() == 1);
	}
}

TEST_CASE("Subtracting numbers")
{
	SECTION("Subtraction of 1/2 and 1/6 with expectation of 1/3")
	{
		CRational rational1(1, 2);
		CRational rational2(1, 6);
		auto result = rational1 - rational2;
		REQUIRE(result.GetNumerator() == 1);
		REQUIRE(result.GetDenominator() == 3);
	}

	SECTION("Subtraction of 1/2 and 1 with expectation of -1/2")
	{
		CRational rational(1, 2);
		auto result = rational - 1;
		REQUIRE(result.GetNumerator() == -1);
		REQUIRE(result.GetDenominator() == 2);
	}

	SECTION("Subtraction of 1 and 1/2 with expectation of 1/2")
	{
		CRational rational(1, 2);
		auto result = 1 - rational;
		REQUIRE(result.GetNumerator() == 1);
		REQUIRE(result.GetDenominator() == 2);
	}

	SECTION("Subtraction of -1/2 and -1/4 with expectation of -1/4")
	{
		CRational rational1(-1, 2);
		CRational rational2(-1, 4);
		auto result = rational1 - rational2;
		REQUIRE(result.GetNumerator() == -1);
		REQUIRE(result.GetDenominator() == 4);
	}

	SECTION("Subtraction of -1/2 and -1/2 with expectation of 0")
	{
		CRational rational1(-1, 2);
		CRational rational2(-1, 2);
		auto result = rational1 - rational2;
		REQUIRE(result.GetNumerator() == 0);
		REQUIRE(result.GetDenominator() == 1);
	}
}

TEST_CASE("Multiplication of numbers")
{
	SECTION("Multiplication of 1/2 and 2/3 with expectation of 1/3")
	{
		CRational rational1(1, 2);
		CRational rational2(2, 3);
		auto result = rational1 * rational2;
		REQUIRE(result.GetNumerator() == 1);
		REQUIRE(result.GetDenominator() == 3);
	}

	SECTION("Multiplication of 1/2 and -3 with expectation of -3/2")
	{
		CRational rational(1, 2);
		auto result = rational * -3;
		REQUIRE(result.GetNumerator() == -3);
		REQUIRE(result.GetDenominator() == 2);
	}

	SECTION("Multiplication of 7 and 2/3 with expectation of 14/3")
	{
		CRational rational(2, 3);
		auto result = 7 * rational;
		REQUIRE(result.GetNumerator() == 14);
		REQUIRE(result.GetDenominator() == 3);
	}

	SECTION("Multiplication of -1/2 and 0 with expectation of 0")
	{
		CRational rational1(-1, 2);
		CRational rational2(0);
		auto result = rational1 * rational2;
		REQUIRE(result.GetNumerator() == 0);
		REQUIRE(result.GetDenominator() == 1);
	}
}

TEST_CASE("Dividing numbers")
{
	SECTION("Dividing of 1/2 and 2/3 with expectation of 3/4")
	{
		CRational rational1(1, 2);
		CRational rational2(2, 3);
		auto result = rational1 / rational2;
		REQUIRE(result.GetNumerator() == 3);
		REQUIRE(result.GetDenominator() == 4);
	}

	SECTION("Dividing of 1/2 and 5 with expectation of 1/10")
	{
		CRational rational(1, 2);
		auto result = rational / 5;
		REQUIRE(result.GetNumerator() == 1);
		REQUIRE(result.GetDenominator() == 10);
	}

	SECTION("Dividing of 7 and 2/3 with expectation of 21/2")
	{
		CRational rational(2, 3);
		auto result = 7 / rational;
		REQUIRE(result.GetNumerator() == 21);
		REQUIRE(result.GetDenominator() == 2);
	}

	SECTION("Dividing of 0 and -1/2 with expectation of 0")
	{
		CRational rational1(0);
		CRational rational2(-1, 2);
		auto result = rational1 / rational2;
		REQUIRE(result.GetNumerator() == 0);
		REQUIRE(result.GetDenominator() == 1);
	}

	SECTION("Dividing of -1/2 and 0 with expectation of std::invalid_argument")
	{
		CRational rational1(-1, 2);
		REQUIRE_THROWS_AS(rational1 / 0, std::invalid_argument);
	}
}

TEST_CASE("Summation of numbers with assignment")
{
	SECTION("Summation of 1/2 and 1/6 with expectation of 2/3")
	{
		CRational rational1(1, 2);
		CRational rational2(1, 6);
		rational1 += rational2;
		REQUIRE(rational1.GetNumerator() == 2);
		REQUIRE(rational1.GetDenominator() == 3);
	}

	SECTION("Summation of 1/2 and 1 with expectation of 3/2")
	{
		CRational rational(1, 2);
		rational += 1;
		REQUIRE(rational.GetNumerator() == 3);
		REQUIRE(rational.GetDenominator() == 2);
	}

	SECTION("Summation of 1/2 and -1/2 with expectation of 0")
	{
		CRational rational1(1, 2);
		CRational rational2(-1, 2);
		rational1 += rational2;
		REQUIRE(rational1.GetNumerator() == 0);
		REQUIRE(rational1.GetDenominator() == 1);
	}
}

TEST_CASE("Subtracting of numbers with assignment")
{
	SECTION("Subtracting of 1/2 and 1/6 with expectation of 1/3")
	{
		CRational rational1(1, 2);
		CRational rational2(1, 6);
		rational1 -= rational2;
		REQUIRE(rational1.GetNumerator() == 1);
		REQUIRE(rational1.GetDenominator() == 3);
	}

	SECTION("Subtracting of 1/2 and 1 with expectation of -1/2")
	{
		CRational rational(1, 2);
		rational -= 1;
		REQUIRE(rational.GetNumerator() == -1);
		REQUIRE(rational.GetDenominator() == 2);
	}

	SECTION("Subtracting of -1/2 and -1/2 with expectation of 0")
	{
		CRational rational1(-1, 2);
		CRational rational2(-1, 2);
		rational1 -= rational2;
		REQUIRE(rational1.GetNumerator() == 0);
		REQUIRE(rational1.GetDenominator() == 1);
	}
}

TEST_CASE("Multiplication of numbers with assignment")
{
	SECTION("Multiplication of 1/2 and 2/3 with expectation of 1/3")
	{
		CRational rational1(1, 2);
		CRational rational2(2, 3);
		rational1 *= rational2;
		REQUIRE(rational1.GetNumerator() == 1);
		REQUIRE(rational1.GetDenominator() == 3);
	}

	SECTION("Multiplication of 1/2 and 3 with expectation of 3/2")
	{
		CRational rational(1, 2);
		rational *= 3;
		REQUIRE(rational.GetNumerator() == 3);
		REQUIRE(rational.GetDenominator() == 2);
	}

	SECTION("Multiplication of 0 and 0 with expectation of 0")
	{
		CRational rational1(0);
		CRational rational2(0);
		rational1 *= rational2;
		REQUIRE(rational1.GetNumerator() == 0);
		REQUIRE(rational1.GetDenominator() == 1);
	}
}

TEST_CASE("Dividing of numbers with assignment")
{
	SECTION("Dividing of 1/2 and 2/3 with expectation of 3/4")
	{
		CRational rational1(1, 2);
		CRational rational2(2, 3);
		rational1 /= rational2;
		REQUIRE(rational1.GetNumerator() == 3);
		REQUIRE(rational1.GetDenominator() == 4);
	}

	SECTION("Dividing of 1/2 and 3 with expectation of 1/6")
	{
		CRational rational(1, 2);
		rational /= 3;
		REQUIRE(rational.GetNumerator() == 1);
		REQUIRE(rational.GetDenominator() == 6);
	}

	SECTION("Dividing of 3/4 and 3/8 with expectation of 2/1")
	{
		CRational rational1(3, 4);
		CRational rational2(3, 8);
		rational1 /= rational2;
		REQUIRE(rational1.GetNumerator() == 2);
		REQUIRE(rational1.GetDenominator() == 1);
	}

	SECTION("Dividing of 0 and 1 with expectation of 0")
	{
		CRational rational1(0);
		CRational rational2(1);
		rational1 /= rational2;
		REQUIRE(rational1.GetNumerator() == 0);
		REQUIRE(rational1.GetDenominator() == 1);
	}

	SECTION("Dividing of -1/2 and 0 with expectation of std::invalid_argument")
	{
		CRational rational1(-1, 2);
		REQUIRE_THROWS_AS(rational1 /= 0, std::invalid_argument);
	}
}

TEST_CASE("Equality of rational numbers")
{
	SECTION("Equality of 1/2 and 1/2 with expectation of true")
	{
		CRational rational1(1, 2);
		CRational rational2(1, 2);
		REQUIRE((rational1 == rational2) == true);
	}

	SECTION("Equality of 1/2 and 2/3 with expectation of false")
	{
		CRational rational1(1, 2);
		CRational rational2(2, 3);
		REQUIRE((rational1 == rational2) == false);
	}

	SECTION("Equality of 4/1 and 4 with expectation of true")
	{
		CRational rational(4, 1);
		REQUIRE((rational == 4) == true);
	}

	SECTION("Equality of 1/2 and 7 with expectation of false")
	{
		CRational rational(1, 2);
		REQUIRE((rational == 7) == false);
	}

	SECTION("Equality of 3 and 3/1 with expectation of true")
	{
		CRational rational(3, 1);
		REQUIRE((3 == rational) == true);
	}

	SECTION("Equality of 3 and 2/3 with expectation of false")
	{
		CRational rational(2, 3);
		REQUIRE((3 == rational) == false);
	}
}

TEST_CASE("Inequality of rational numbers")
{
	SECTION("Inequality of 1/2 and 1/2 with expectation of false")
	{
		CRational rational1(1, 2);
		CRational rational2(1, 2);
		REQUIRE((rational1 != rational2) == false);
	}

	SECTION("Inequality of 1/2 and 2/3 with expectation of true")
	{
		CRational rational1(1, 2);
		CRational rational2(2, 3);
		REQUIRE((rational1 != rational2) == true);
	}

	SECTION("Inequality of 4/1 and 4 with expectation of false")
	{
		CRational rational(4, 1);
		REQUIRE((rational != 4) == false);
	}

	SECTION("Inequality of 1/2 and 7 with expectation of true")
	{
		CRational rational(1, 2);
		REQUIRE((rational != 7) == true);
	}

	SECTION("Inequality of 3 and 3/1 with expectation of false")
	{
		CRational rational(3, 1);
		REQUIRE((3 != rational) == false);
	}

	SECTION("Inequality of 3 and 2/3 with expectation of true")
	{
		CRational rational(2, 3);
		REQUIRE((3 != rational) == true);
	}
}

TEST_CASE("The operation is smaller")
{
	SECTION("Smaller of 1/2 and 2/3 with expectation of true")
	{
		CRational rational1(1, 2);
		CRational rational2(2, 3);
		REQUIRE((rational1 < rational2) == true);
	}

	SECTION("Smaller of 1/2 and 7 with expectation of true")
	{
		CRational rational(1, 2);
		REQUIRE((rational < 7) == true);
	}

	SECTION("Smaller of 2/3 and 1/2 with expectation of false")
	{
		CRational rational1(2, 3);
		CRational rational2(1, 2);
		REQUIRE((rational1 < rational2) == false);
	}

	SECTION("Smaller of 7 and 1/2 with expectation of false")
	{
		CRational rational(1, 2);
		REQUIRE((7 < rational) == false);
	}

	SECTION("Smaller of -1/3 and 1/3 with expectation of true")
	{
		CRational rational1(-1, 3);
		CRational rational2(1, 3);
		REQUIRE((rational1 < rational2) == true);
	}
}

TEST_CASE("The operation is greater")
{
	SECTION("Greater of 2/3 and 1/2 with expectation of true")
	{
		CRational rational1(2, 3);
		CRational rational2(1, 2);
		REQUIRE((rational1 > rational2) == true);
	}

	SECTION("Greater of 3/1 and 2 with expectation of true")
	{
		CRational rational(3, 1);
		REQUIRE((rational > 2) == true);
	}

	SECTION("Greater of 1/2 and 2/3 with expectation of false")
	{
		CRational rational1(1, 2);
		CRational rational2(2, 3);
		REQUIRE((rational1 > rational2) == false);
	}

	SECTION("Greater of 2 and 3/1 with expectation of false")
	{
		CRational rational(3, 1);
		REQUIRE((2 > rational) == false);
	}

	SECTION("Greater of 1/3 and -1/3 with expectation of true")
	{
		CRational rational1(1, 3);
		CRational rational2(-1, 3);
		REQUIRE((rational1 > rational2) == true);
	}
}

TEST_CASE("The operation is smaller than or equal to")
{
	SECTION("Smaller or equal of 1/2 and 1/3 with expectation of false")
	{
		CRational rational1(1, 2);
		CRational rational2(1, 3);
		REQUIRE((rational1 <= rational2) == false);
	}

	SECTION("Smaller or equal of 3 and 7/2 with expectation of true")
	{
		CRational rational(7, 2);
		REQUIRE((3 <= rational) == true);
	}

	SECTION("Smaller or equal of 1/3 and 1/3 with expectation of true")
	{
		CRational rational1(1, 3);
		CRational rational2(1, 3);
		REQUIRE((rational1 <= rational2) == true);
	}

	SECTION("Smaller or equal of 0 and 0 with expectation of true")
	{
		CRational rational1(0, 1);
		CRational rational2(0, 1);
		REQUIRE((rational1 <= rational2) == true);
	}
}

TEST_CASE("The operation is greater than or equal to")
{
	SECTION("Greater or equal of 1/2 and 1/3 with expectation of true")
	{
		CRational rational1(1, 2);
		CRational rational2(1, 3);
		REQUIRE((rational1 >= rational2) == true);
	}

	SECTION("Greater or equal of 3 and 8/2 with expectation of false")
	{
		CRational rational(8, 2);
		REQUIRE((3 >= rational) == false);
	}

	SECTION("Greater or equal of 1/3 and 1/3 with expectation of true")
	{
		CRational rational1(1, 3);
		CRational rational2(1, 3);
		REQUIRE((rational1 >= rational2) == true);
	}

	SECTION("Greater or equal of 0 and 0 with expectation of true")
	{
		CRational rational1(0, 1);
		CRational rational2(0, 1);
		REQUIRE((rational1 >= rational2) == true);
	}
}

TEST_CASE("Printing a rational number into a stream")
{
	SECTION("Print 1/2")
	{
		std::stringstream ss;
		CRational rational(1, 2);
		ss << rational;
		REQUIRE(ss.str() == "1/2");
	}

	SECTION("Print -1/2")
	{
		std::stringstream ss;
		CRational rational(-1, 2);
		ss << rational;
		REQUIRE(ss.str() == "-1/2");
	}

	SECTION("Print 0/1")
	{
		std::stringstream ss;
		CRational rational(0, 1);
		ss << rational;
		REQUIRE(ss.str() == "0/1");
	}
}

TEST_CASE("Reading a rational number from a stream")
{
	SECTION("Read 1/2")
	{
		std::stringstream ss("1/2");
		CRational rational;
		ss >> rational;
		REQUIRE(rational.GetNumerator() == 1);
		REQUIRE(rational.GetDenominator() == 2);
	}

	SECTION("Read -1/2")
	{
		std::stringstream ss("-1/2");
		CRational rational;
		ss >> rational;
		REQUIRE(rational.GetNumerator() == -1);
		REQUIRE(rational.GetDenominator() == 2);
	}

	SECTION("Read 0/1")
	{
		std::stringstream ss("0/1");
		CRational rational;
		ss >> rational;
		REQUIRE(rational.GetNumerator() == 0);
		REQUIRE(rational.GetDenominator() == 1);
	}

	SECTION("Errors reading from the stream")
	{
		SECTION("Empty input")
		{
			std::stringstream ss("");
			CRational rational;
			ss >> rational;
			REQUIRE(ss.fail() == true);
		}

		SECTION("Input without numerator")
		{
			std::stringstream ss("/1");
			CRational rational;
			ss >> rational;
			REQUIRE(ss.fail() == true);
		}

		SECTION("Not a rational number")
		{
			std::stringstream ss("1.32");
			CRational rational;
			ss >> rational;
			REQUIRE(ss.fail() == true);
		}

		SECTION("Not a rational number")
		{
			std::stringstream ss("20");
			CRational rational;
			ss >> rational;
			REQUIRE(ss.fail() == true);
		}

		SECTION("Incorrect input")
		{
			std::stringstream ss("abc");
			CRational rational;
			ss >> rational;
			REQUIRE(ss.fail() == true);
		}

		SECTION("Incorrect input")
		{
			std::stringstream ss("a/c");
			CRational rational;
			ss >> rational;
			REQUIRE(ss.fail() == true);
		}

		SECTION("Incorrect input")
		{
			std::stringstream ss("12&4");
			CRational rational;
			ss >> rational;
			REQUIRE(ss.fail() == true);
		}
	}
}
