#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../vector.h"

SCENARIO("Data reading works correctly")
{
	std::istringstream iss("-1 -2 -3 -4 5.123");
	std::vector<double> perfectData = {-1.000, -2.000, -3.000, -4.000, 5.123};
	REQUIRE(ReadDoubleVector(iss).value() == perfectData);
	iss.clear();

	iss.str("");
	perfectData = {};
	REQUIRE(ReadDoubleVector(iss).value() == perfectData);
	iss.clear();

	iss.str("a b c");
	REQUIRE(ReadDoubleVector(iss).has_value() == false);
}

SCENARIO("Data printing works correctly")
{
	std::ostringstream oss;
	std::vector<double> data = {-1.000, -2.000, -3.000, -4.000, 5.123};
	PrintNumbers(oss, data);
	REQUIRE(oss.str() == "-1.000 -2.000 -3.000 -4.000 5.123 \n");
}

SCENARIO("Each element must be multiplied by the minimum element")
{
	std::vector<double> data = {-1.000, -2.000, -3.000, -4.000, 5.123};
	std::vector<double> result = {4.000, 8.000, 12.000, 16.000, -20.492};
	MultiplyArrayElementsByMinimumElement(data);
	REQUIRE(data == result);
}

SCENARIO("Sorting a vector of double numbers in ascending order")
{
	std::vector<double> data = {4.000, 8.000, 12.000, 16.000, -20.492};
	std::vector<double> result = {-20.492, 4.000, 8.000, 12.000, 16.000};
	SortVector(data);
	REQUIRE(data == result);
}
