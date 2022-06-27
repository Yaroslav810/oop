#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../CMyArray.h"

TEST_CASE("Creating CMyArray")
{
	SECTION("Empty constructor")
	{
		CMyArray<std::string> array;
		REQUIRE(array.GetSize() == 0);
		REQUIRE_THROWS_AS(array[0], std::out_of_range);
	}

	SECTION("Constructor with size")
	{
		CMyArray<std::string> array(2);
		REQUIRE(array.GetSize() == 2);
		REQUIRE_NOTHROW(array[0]);
		REQUIRE_NOTHROW(array[1]);
		REQUIRE_THROWS_AS(array[2], std::out_of_range);
	}
}

TEST_CASE("Push")
{
	SECTION("Empty constructor")
	{
		CMyArray<std::string> array(0);
		REQUIRE(array.GetSize() == 0);
		REQUIRE_NOTHROW(array.Push("Hello"));
		REQUIRE(array[0] == "Hello");
		REQUIRE_THROWS_AS(array[1], std::out_of_range);
		REQUIRE_NOTHROW(array.Push("World"));
		REQUIRE(array[0] == "Hello");
		REQUIRE(array[1] == "World");
		REQUIRE_THROWS_AS(array[2], std::out_of_range);
	}
}

TEST_CASE("Clear")
{
	CMyArray<std::string> array(0);
	array.Push("Hello");
	array.Push("World");
	REQUIRE(array.GetSize() == 2);

	REQUIRE_NOTHROW(array.Clear());
	REQUIRE(array.GetSize() == 0);
	REQUIRE_THROWS_AS(array[0], std::out_of_range);
}

TEST_CASE("Resize")
{
	CMyArray<std::string> array;
	REQUIRE(array.GetSize() == 0);

	REQUIRE_NOTHROW(array.Resize(10));
	REQUIRE(array.GetSize() == 10);

	REQUIRE_NOTHROW(array.Resize(5));
	REQUIRE(array.GetSize() == 5);
}

TEST_CASE("[]")
{
	CMyArray<std::string> array;
	REQUIRE(array.GetSize() == 0);

	REQUIRE_NOTHROW(array.Resize(10));
	REQUIRE(array.GetSize() == 10);

	REQUIRE_NOTHROW(array.Resize(5));
	REQUIRE(array.GetSize() == 5);
}
