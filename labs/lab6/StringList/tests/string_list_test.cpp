#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../CStringList.h"

TEST_CASE("Creating list")
{
	CStringList list;
	REQUIRE(list.GetSize() == 0);
	REQUIRE(list.IsEmpty());
}

TEST_CASE("PushBack")
{
	CStringList list;
	REQUIRE(list.IsEmpty());
	REQUIRE_NOTHROW(list.PushBack("Hello"));
	REQUIRE(list.GetSize() == 1);
	REQUIRE(list.GetFront() == "Hello");
	REQUIRE(list.GetBack() == "Hello");
	REQUIRE_NOTHROW(list.PushBack(" "));
	REQUIRE(list.GetSize() == 2);
	REQUIRE(list.GetFront() == "Hello");
	REQUIRE(list.GetBack() == " ");
	REQUIRE_NOTHROW(list.PushBack("World"));
	REQUIRE(list.GetSize() == 3);
	REQUIRE(list.GetFront() == "Hello");
	REQUIRE(list.GetBack() == "World");
}

TEST_CASE("PushFront")
{
	CStringList list;
	REQUIRE(list.IsEmpty());
	REQUIRE_NOTHROW(list.PushFront("Hello"));
	REQUIRE(list.GetSize() == 1);
	REQUIRE(list.GetFront() == "Hello");
	REQUIRE(list.GetBack() == "Hello");
	REQUIRE_NOTHROW(list.PushFront(" "));
	REQUIRE(list.GetSize() == 2);
	REQUIRE(list.GetFront() == " ");
	REQUIRE(list.GetBack() == "Hello");
	REQUIRE_NOTHROW(list.PushFront("World"));
	REQUIRE(list.GetSize() == 3);
	REQUIRE(list.GetFront() == "World");
	REQUIRE(list.GetBack() == "Hello");
}

TEST_CASE("Multi PushBack")
{
	CStringList list;
	REQUIRE(list.IsEmpty());
	REQUIRE_NOTHROW(list.PushBack("Hello").PushBack(" ").PushBack("World"));
	REQUIRE(list.GetSize() == 3);
	REQUIRE(list.GetFront() == "Hello");
	REQUIRE(list.GetBack() == "World");
}

TEST_CASE("Multi PushFront")
{
	CStringList list;
	REQUIRE(list.IsEmpty());
	REQUIRE_NOTHROW(list.PushFront("Hello").PushFront(" ").PushFront("World"));
	REQUIRE(list.GetSize() == 3);
	REQUIRE(list.GetFront() == "World");
	REQUIRE(list.GetBack() == "Hello");
}

TEST_CASE("GetBack")
{
	CStringList list;
	REQUIRE_THROWS_AS(list.GetBack(), std::logic_error);
	REQUIRE_NOTHROW(list.PushBack("Hello"));
	REQUIRE(list.GetBack() == "Hello");
}

TEST_CASE("GetFront")
{
	CStringList list;
	REQUIRE_THROWS_AS(list.GetFront(), std::logic_error);
	REQUIRE_NOTHROW(list.PushBack("Hello"));
	REQUIRE(list.GetFront() == "Hello");
}

TEST_CASE("Clear")
{
	CStringList list;
	REQUIRE(list.IsEmpty());
	REQUIRE_NOTHROW(list.PushFront("Hello").PushFront(" ").PushFront("World"));
	REQUIRE(list.GetSize() == 3);
	REQUIRE_NOTHROW(list.Clear());
	REQUIRE(list.GetSize() == 0);
	REQUIRE_NOTHROW(list.Clear());
	REQUIRE(list.GetSize() == 0);
}
