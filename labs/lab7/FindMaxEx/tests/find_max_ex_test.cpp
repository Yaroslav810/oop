#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../FindMaxEx.h"

TEST_CASE("Function Test")
{
	SECTION("Vector = [1, 2, 3, 4] with max = 4")
	{
		std::vector<int> numbers = {1, 2, 3, 4};
		int max = 0;
		auto result = FindMaxEx(numbers, max, [](int a, int b) { return a < b; });
		REQUIRE(result == true);
		REQUIRE(max == 4);
	}

	SECTION("Vector = [1.5, 1.6, 1.4] with max = 1.6")
	{
		std::vector<double> numbers = {1.5, 1.6, 1.4};
		double max;
		auto result = FindMaxEx(numbers, max, [](double a, double b) { return a < b; });
		REQUIRE(result == true);
		REQUIRE(max == 1.6);
	}

	SECTION("Vector = [-1.5, -1.6, 1.4] with max = 1.4")
	{
		std::vector<double> numbers = {-1.5, -1.6, 1.4};
		double max;
		auto result = FindMaxEx(numbers, max, [](double a, double b) { return a < b; });
		REQUIRE(result == true);
		REQUIRE(max == 1.4);
	}

	SECTION("Vector = ['c', 'b', 'a'] with max = 'c'")
	{
		std::vector<char> chars = {'c', 'b', 'a'};
		char max;
		auto result = FindMaxEx(chars, max, [](char a, char b) { return a < b; });
		REQUIRE(result == true);
		REQUIRE(max == 'c');
	}

	SECTION("Vector = ['abc', 'cde', 'bcd'] with max = 'cde'")
	{
		std::vector<std::string> strings = {"abc", "cde", "bcd"};
		std::string max;
		auto result = FindMaxEx(strings, max, [](std::string a, std::string b) { return a < b; });
		REQUIRE(result == true);
		REQUIRE(max == "cde");
	}

	SECTION("Vector = [1] with max = 1")
	{
		std::vector<int> numbers = {1};
		int max = 0;
		auto result = FindMaxEx(numbers, max, [](int a, int b) { return a < b; });
		REQUIRE(result == true);
		REQUIRE(max == 1);
	}

	SECTION("Vector = [{'Alex', 16}, {'Bob', 32}, {'Petr', 24}] with max age")
	{
		struct Person
		{
			std::string name;
			int age{};
		};
		std::vector<Person> persons = {
			{"Alex", 16},
			{"Bob", 32},
			{"Petr", 24},
		};
		Person max;
		auto result = FindMaxEx(persons, max, [](const Person& a, const Person& b) { return a.age < b.age; });
		REQUIRE(result == true);
		REQUIRE(max.name == "Bob");
		REQUIRE(max.age == 32);
	}
}

TEST_CASE("All max value")
{
	std::vector<int> numbers = {1, 1, 1, 1, 1};
	int max = 0;
	auto result = FindMaxEx(numbers, max, [](int a, int b) { return a < b; });
	REQUIRE(result == true);
	REQUIRE(max == 1);
}

TEST_CASE("Some max value")
{
	std::vector<int> numbers = {1, 5, 12, -1, -5, 12};
	int max = 0;
	auto result = FindMaxEx(numbers, max, [](int a, int b) { return a < b; });
	REQUIRE(result == true);
	REQUIRE(max == 12);
}

TEST_CASE("Empty vector")
{
	std::vector<int> numbers = {};
	int max = 0;
	auto result = FindMaxEx(numbers, max, [](int a, int b) { return a < b; });
	REQUIRE(result == false);
	REQUIRE(max == 0);
}
