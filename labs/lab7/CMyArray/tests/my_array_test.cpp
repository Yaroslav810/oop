#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../CMyArray.h"

TEST_CASE("Creating CMyArray")
{
	SECTION("Empty constructor string")
	{
		CMyArray<std::string> array;
		REQUIRE(array.GetSize() == 0);
		REQUIRE_THROWS_AS(array[0], std::out_of_range);
	}

	SECTION("Empty constructor int")
	{
		CMyArray<int> array;
		REQUIRE(array.GetSize() == 0);
		REQUIRE_THROWS_AS(array[0], std::out_of_range);
	}

	SECTION("Empty constructor struct")
	{
		struct Point
		{
			int x;
			int y;
		};
		CMyArray<Point> array;
		REQUIRE(array.GetSize() == 0);
		REQUIRE_THROWS_AS(array[0], std::out_of_range);
	}

	SECTION("Constructor with size string")
	{
		CMyArray<std::string> array(2);
		REQUIRE(array.GetSize() == 2);
		REQUIRE_NOTHROW(array[0]);
		REQUIRE(array[0] == "");
		REQUIRE_NOTHROW(array[1]);
		REQUIRE(array[1] == "");
		REQUIRE_THROWS_AS(array[2], std::out_of_range);
	}

	SECTION("Constructor with size int")
	{
		CMyArray<int> array(2);
		REQUIRE(array.GetSize() == 2);
		REQUIRE_NOTHROW(array[0]);
		REQUIRE(array[0] == 0);
		REQUIRE_NOTHROW(array[1]);
		REQUIRE(array[1] == 0);
		REQUIRE_THROWS_AS(array[2], std::out_of_range);
	}

	SECTION("Constructor with size struct")
	{
		struct Point
		{
			int x;
			int y;
		};
		CMyArray<Point> array(1);
		REQUIRE(array.GetSize() == 1);
		REQUIRE_NOTHROW(array[0]);
		REQUIRE((array[0].x == 0 && array[0].y == 0));
		REQUIRE_THROWS_AS(array[1], std::out_of_range);
	}
}

TEST_CASE("Push")
{
	SECTION("string")
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

	SECTION("int")
	{
		CMyArray<int> array(0);
		REQUIRE(array.GetSize() == 0);
		REQUIRE_NOTHROW(array.Push(1));
		REQUIRE(array[0] == 1);
		REQUIRE_THROWS_AS(array[1], std::out_of_range);
		REQUIRE_NOTHROW(array.Push(2));
		REQUIRE(array[0] == 1);
		REQUIRE(array[1] == 2);
		REQUIRE_THROWS_AS(array[2], std::out_of_range);
	}

	SECTION("struct")
	{
		struct Point
		{
			int x;
			int y;
		};
		CMyArray<Point> array(0);
		REQUIRE(array.GetSize() == 0);
		REQUIRE_NOTHROW(array.Push({ 1, 2 }));
		REQUIRE((array[0].x == 1 && array[0].y == 2));
		REQUIRE_THROWS_AS(array[1], std::out_of_range);
		REQUIRE_NOTHROW(array.Push({ 3, 4 }));
		REQUIRE((array[0].x == 1 && array[0].y == 2));
		REQUIRE((array[1].x == 3 && array[1].y == 4));
		REQUIRE_THROWS_AS(array[2], std::out_of_range);
	}
}

TEST_CASE("Clear")
{
	SECTION("string")
	{
		CMyArray<std::string> array(0);
		array.Push("Hello");
		array.Push("World");
		REQUIRE(array.GetSize() == 2);

		REQUIRE_NOTHROW(array.Clear());
		REQUIRE(array.GetSize() == 0);
		REQUIRE_THROWS_AS(array[0], std::out_of_range);
	}

	SECTION("int")
	{
		CMyArray<int> array(0);
		array.Push(0);
		array.Push(1);
		REQUIRE(array.GetSize() == 2);

		REQUIRE_NOTHROW(array.Clear());
		REQUIRE(array.GetSize() == 0);
		REQUIRE_THROWS_AS(array[0], std::out_of_range);
	}
}

TEST_CASE("Resize")
{
	SECTION("string")
	{
		CMyArray<std::string> array;
		REQUIRE(array.GetSize() == 0);

		REQUIRE_NOTHROW(array.Push("Hello"));
		REQUIRE_NOTHROW(array.Push("World"));

		REQUIRE_NOTHROW(array.Resize(10));
		REQUIRE(array.GetSize() == 10);
		REQUIRE(array[0] == "Hello");
		REQUIRE(array[1] == "World");
		REQUIRE(array[2].empty());

		REQUIRE_NOTHROW(array.Resize(1));
		REQUIRE(array.GetSize() == 1);
		REQUIRE(array[0] == "Hello");
		REQUIRE_THROWS_AS(array[1], std::out_of_range);
	}

	SECTION("int")
	{
		CMyArray<int> array;
		REQUIRE(array.GetSize() == 0);

		REQUIRE_NOTHROW(array.Push(1));
		REQUIRE_NOTHROW(array.Push(2));

		REQUIRE_NOTHROW(array.Resize(10));
		REQUIRE(array.GetSize() == 10);
		REQUIRE(array[0] == 1);
		REQUIRE(array[1] == 2);
		REQUIRE(array[2] == 0);

		REQUIRE_NOTHROW(array.Resize(1));
		REQUIRE(array.GetSize() == 1);
		REQUIRE(array[0] == 1);
		REQUIRE_THROWS_AS(array[1], std::out_of_range);
	}
}

TEST_CASE("copy constructor")
{
	CMyArray<std::string> array1(4);
	array1.Push("Hello");
	array1.Push(" ");
	array1.Push("World");
	REQUIRE(array1.GetSize() == 7);

	CMyArray<std::string> array2(array1);
	REQUIRE(array2.GetSize() == 7);

	array2.Push("!");
	REQUIRE(array1.GetSize() == 7);
	REQUIRE(array2.GetSize() == 8);
}

TEST_CASE("copying by assignment")
{
	CMyArray<std::string> array1(4);
	array1.Push("Hello");
	array1.Push(" ");
	array1.Push("World");
	REQUIRE(array1.GetSize() == 7);

	CMyArray<std::string> array2(0);
	REQUIRE(array2.GetSize() == 0);

	array1 = array2;
	REQUIRE(array1.GetSize() == 0);
	REQUIRE(array2.GetSize() == 0);
}

TEST_CASE("move constructor")
{
	CMyArray<std::string> array1(2);
	array1.Push("Hello");
	array1.Push("World");
	REQUIRE(array1.GetSize() == 4);

	CMyArray<std::string> array2(std::move(array1));
	REQUIRE(array1.GetSize() == 0);
	REQUIRE(array2.GetSize() == 4);
	REQUIRE(array2[0] == "");
	REQUIRE(array2[1] == "");
	REQUIRE(array2[2] == "Hello");
	REQUIRE(array2[3] == "World");
	REQUIRE_THROWS_AS(array2[4], std::out_of_range);
}

TEST_CASE("moving by assignment")
{
	CMyArray<std::string> array1(2);
	array1.Push("Hello");
	array1.Push("World");
	REQUIRE(array1.GetSize() == 4);

	CMyArray<std::string> array2(0);
	REQUIRE(array2.GetSize() == 0);

	array2 = std::move(array1);
	REQUIRE(array1.GetSize() == 0);
	REQUIRE(array2.GetSize() == 4);
	REQUIRE(array2[0] == "");
	REQUIRE(array2[1] == "");
	REQUIRE(array2[2] == "Hello");
	REQUIRE(array2[3] == "World");
	REQUIRE_THROWS_AS(array2[4], std::out_of_range);
}

TEST_CASE("iterator")
{
	SECTION("string")
	{
		CMyArray<std::string> array;
		array.Push("Hello");
		array.Push(" ");
		array.Push("World");
		array.Push("!");

		SECTION("*")
		{
			CMyArray<std::string>::iterator beginIt = array.begin();
			REQUIRE(*beginIt == "Hello");

			CMyArray<std::string>::iterator endIt = array.end();
			REQUIRE(*(endIt - 1) == "!");
		}

		SECTION("++")
		{
			CMyArray<std::string>::iterator it = array.begin();
			for (size_t i = 0; i < 3; ++i, ++it)
			{
				REQUIRE(array[i] == *it);
			}

			REQUIRE(*it == "!");
		}

		SECTION("--")
		{
			CMyArray<std::string>::iterator it = array.end();
			REQUIRE(*(it - 1) == "!");
			--it;
			REQUIRE(*it == "!");
		}

		SECTION("+=")
		{
			CMyArray<std::string>::iterator it = array.begin();
			REQUIRE(*it == "Hello");
			REQUIRE_NOTHROW(it += 2);
			REQUIRE(*it == "World");
		}

		SECTION("-=")
		{
			CMyArray<std::string>::iterator it = array.end();
			REQUIRE(*(it - 1) == "!");
			REQUIRE_NOTHROW(it -= 2);
			REQUIRE(*it == "World");
		}

		SECTION("-")
		{
			CMyArray<std::string>::iterator endIt = array.end();
			CMyArray<std::string>::iterator beginIt = endIt - 4;
			REQUIRE(*beginIt == "Hello");
		}

		SECTION("-")
		{
			CMyArray<std::string>::iterator beginIt = array.begin();
			CMyArray<std::string>::iterator endIt = array.end();
			REQUIRE(endIt - beginIt == 4);
		}

		SECTION("<")
		{
			CMyArray<std::string>::iterator beginIt = array.begin();
			CMyArray<std::string>::iterator endIt = array.end();
			REQUIRE((beginIt < endIt) == true);
			REQUIRE((endIt < beginIt) == false);
			REQUIRE((beginIt < beginIt) == false);
		}

		SECTION(">")
		{
			CMyArray<std::string>::iterator beginIt = array.begin();
			CMyArray<std::string>::iterator endIt = array.end();
			REQUIRE((endIt > beginIt) == true);
			REQUIRE((beginIt > endIt) == false);
			REQUIRE((endIt > endIt) == false);
		}

		SECTION(">=")
		{
			CMyArray<std::string>::iterator beginIt = array.begin();
			CMyArray<std::string>::iterator endIt = array.end();
			REQUIRE((endIt >= beginIt) == true);
			REQUIRE((beginIt >= endIt) == false);
			REQUIRE((beginIt >= beginIt) == true);
		}

		SECTION("<=")
		{
			CMyArray<std::string>::iterator beginIt = array.begin();
			CMyArray<std::string>::iterator endIt = array.end();
			REQUIRE((endIt <= beginIt) == false);
			REQUIRE((beginIt <= endIt) == true);
			REQUIRE((beginIt <= beginIt) == true);
		}

		SECTION("[]")
		{
			CMyArray<std::string>::iterator beginIt = array.begin();
			CMyArray<std::string>::iterator endIt = array.end();
			REQUIRE(beginIt[0] == "Hello");
		}
	}
}

TEST_CASE("const iterator")
{
	SECTION("string")
	{
		CMyArray<std::string> array;
		array.Push("Hello");
		array.Push("World");

		CMyArray<std::string>::const_iterator beginIt = array.begin();
		REQUIRE(*beginIt == "Hello");

		CMyArray<std::string>::const_iterator endIt = array.end();
		REQUIRE(*(endIt - 1) == "World");
	}

	SECTION("int")
	{
		CMyArray<int> array;
		array.Push(1);
		array.Push(2);

		CMyArray<int>::const_iterator beginIt = array.begin();
		REQUIRE(*beginIt == 1);

		CMyArray<int>::const_iterator endIt = array.end();
		REQUIRE(*(endIt - 1) == 2);
	}
}

TEST_CASE("const iterator full")
{
	SECTION("string")
	{
		CMyArray<std::string> array;
		array.Push("Hello");
		array.Push(" ");
		array.Push("World");
		array.Push("!");

		SECTION("*")
		{
			CMyArray<std::string>::const_iterator beginIt = array.begin();
			REQUIRE(*beginIt == "Hello");

			CMyArray<std::string>::const_iterator endIt = array.end();
			REQUIRE(*(endIt - 1) == "!");
		}

		SECTION("++")
		{
			CMyArray<std::string>::const_iterator it = array.begin();
			for (size_t i = 0; i < 3; ++i, ++it)
			{
				REQUIRE(array[i] == *it);
			}

			REQUIRE(*it == "!");
		}

		SECTION("--")
		{
			CMyArray<std::string>::const_iterator it = array.end();
			REQUIRE(*(it - 1) == "!");
			--it;
			REQUIRE(*it == "!");
		}

		SECTION("+=")
		{
			CMyArray<std::string>::const_iterator it = array.begin();
			REQUIRE(*it == "Hello");
			REQUIRE_NOTHROW(it += 2);
			REQUIRE(*it == "World");
		}

		SECTION("-=")
		{
			CMyArray<std::string>::const_iterator it = array.end();
			REQUIRE(*(it - 1) == "!");
			REQUIRE_NOTHROW(it -= 2);
			REQUIRE(*it == "World");
		}

		SECTION("-")
		{
			CMyArray<std::string>::const_iterator endIt = array.end();
			CMyArray<std::string>::const_iterator beginIt = endIt - 4;
			REQUIRE(*beginIt == "Hello");
		}

		SECTION("-")
		{
			CMyArray<std::string>::const_iterator beginIt = array.begin();
			CMyArray<std::string>::const_iterator endIt = array.end();
			REQUIRE(endIt - beginIt == 4);
		}

		SECTION("<")
		{
			CMyArray<std::string>::const_iterator beginIt = array.begin();
			CMyArray<std::string>::const_iterator endIt = array.end();
			REQUIRE((beginIt < endIt) == true);
			REQUIRE((endIt < beginIt) == false);
			REQUIRE((beginIt < beginIt) == false);
		}

		SECTION(">")
		{
			CMyArray<std::string>::const_iterator beginIt = array.begin();
			CMyArray<std::string>::const_iterator endIt = array.end();
			REQUIRE((endIt > beginIt) == true);
			REQUIRE((beginIt > endIt) == false);
			REQUIRE((endIt > endIt) == false);
		}

		SECTION(">=")
		{
			CMyArray<std::string>::const_iterator beginIt = array.begin();
			CMyArray<std::string>::const_iterator endIt = array.end();
			REQUIRE((endIt >= beginIt) == true);
			REQUIRE((beginIt >= endIt) == false);
			REQUIRE((beginIt >= beginIt) == true);
		}

		SECTION("<=")
		{
			CMyArray<std::string>::const_iterator beginIt = array.begin();
			CMyArray<std::string>::const_iterator endIt = array.end();
			REQUIRE((endIt <= beginIt) == false);
			REQUIRE((beginIt <= endIt) == true);
			REQUIRE((beginIt <= beginIt) == true);
		}

		SECTION("[]")
		{
			CMyArray<std::string>::const_iterator beginIt = array.begin();
			CMyArray<std::string>::const_iterator endIt = array.end();
			REQUIRE(beginIt[0] == "Hello");
		}
	}
}

TEST_CASE("reverse iterator")
{
	SECTION("string")
	{
		CMyArray<std::string> array;
		array.Push("Hello");
		array.Push(" ");
		array.Push("World");
		array.Push("!");

		SECTION("*")
		{
			CMyArray<std::string>::reverse_iterator beginIt = array.rbegin();
			REQUIRE(*beginIt == "!");

			CMyArray<std::string>::reverse_iterator endIt = array.rend();
			REQUIRE(*(endIt - 1) == "Hello");
		}

		SECTION("++")
		{
			CMyArray<std::string>::reverse_iterator it = array.rbegin();
			for (size_t i = 3; i > 0; --i, ++it)
			{
				REQUIRE(array[i] == *it);
			}

			REQUIRE(*it == "Hello");
		}

		SECTION("--")
		{
			CMyArray<std::string>::reverse_iterator it = array.rend();
			REQUIRE(*(it - 1) == "Hello");
			--it;
			REQUIRE(*it == "Hello");
		}

		SECTION("+=")
		{
			CMyArray<std::string>::reverse_iterator it = array.rbegin();
			REQUIRE(*it == "!");
			REQUIRE_NOTHROW(it += 2);
			REQUIRE(*it == " ");
		}

		SECTION("-=")
		{
			CMyArray<std::string>::reverse_iterator it = array.rend();
			REQUIRE(*(it - 1) == "Hello");
			REQUIRE_NOTHROW(it -= 2);
			REQUIRE(*it == " ");
		}

		SECTION("-")
		{
			CMyArray<std::string>::reverse_iterator endIt = array.rend();
			CMyArray<std::string>::reverse_iterator beginIt = endIt - 4;
			REQUIRE(*beginIt == "!");
		}

		SECTION("-")
		{
			CMyArray<std::string>::reverse_iterator beginIt = array.rbegin();
			CMyArray<std::string>::reverse_iterator endIt = array.rend();
			REQUIRE(endIt - beginIt == 4);
		}

		SECTION("<")
		{
			CMyArray<std::string>::reverse_iterator beginIt = array.rbegin();
			CMyArray<std::string>::reverse_iterator endIt = array.rend();
			REQUIRE((beginIt < endIt) == true);
			REQUIRE((endIt < beginIt) == false);
			REQUIRE((beginIt < beginIt) == false);
		}

		SECTION(">")
		{
			CMyArray<std::string>::reverse_iterator beginIt = array.rbegin();
			CMyArray<std::string>::reverse_iterator endIt = array.rend();
			REQUIRE((endIt > beginIt) == true);
			REQUIRE((beginIt > endIt) == false);
			REQUIRE((endIt > endIt) == false);
		}

		SECTION(">=")
		{
			CMyArray<std::string>::reverse_iterator beginIt = array.rbegin();
			CMyArray<std::string>::reverse_iterator endIt = array.rend();
			REQUIRE((endIt >= beginIt) == true);
			REQUIRE((beginIt >= endIt) == false);
			REQUIRE((beginIt >= beginIt) == true);
		}

		SECTION("<=")
		{
			CMyArray<std::string>::reverse_iterator beginIt = array.rbegin();
			CMyArray<std::string>::reverse_iterator endIt = array.rend();
			REQUIRE((endIt <= beginIt) == false);
			REQUIRE((beginIt <= endIt) == true);
			REQUIRE((beginIt <= beginIt) == true);
		}

		SECTION("[]")
		{
			CMyArray<std::string>::reverse_iterator beginIt = array.rbegin();
			CMyArray<std::string>::reverse_iterator endIt = array.rend();
			REQUIRE(beginIt[0] == "!");
		}
	}
}

TEST_CASE("const reverse iterator")
{
	SECTION("string")
	{
		CMyArray<std::string> array;
		array.Push("Hello");
		array.Push(" ");
		array.Push("World");
		array.Push("!");

		SECTION("*")
		{
			CMyArray<std::string>::const_reverse_iterator beginIt = array.rbegin();
			REQUIRE(*beginIt == "!");

			CMyArray<std::string>::const_reverse_iterator endIt = array.rend();
			REQUIRE(*(endIt - 1) == "Hello");
		}

		SECTION("++")
		{
			CMyArray<std::string>::const_reverse_iterator it = array.rbegin();
			for (size_t i = 3; i > 0; --i, ++it)
			{
				REQUIRE(array[i] == *it);
			}

			REQUIRE(*it == "Hello");
		}

		SECTION("--")
		{
			CMyArray<std::string>::const_reverse_iterator it = array.rend();
			REQUIRE(*(it - 1) == "Hello");
			--it;
			REQUIRE(*it == "Hello");
		}

		SECTION("+=")
		{
			CMyArray<std::string>::const_reverse_iterator it = array.rbegin();
			REQUIRE(*it == "!");
			REQUIRE_NOTHROW(it += 2);
			REQUIRE(*it == " ");
		}

		SECTION("-=")
		{
			CMyArray<std::string>::const_reverse_iterator it = array.rend();
			REQUIRE(*(it - 1) == "Hello");
			REQUIRE_NOTHROW(it -= 2);
			REQUIRE(*it == " ");
		}

		SECTION("-")
		{
			CMyArray<std::string>::const_reverse_iterator endIt = array.rend();
			CMyArray<std::string>::const_reverse_iterator beginIt = endIt - 4;
			REQUIRE(*beginIt == "!");
		}

		SECTION("-")
		{
			CMyArray<std::string>::const_reverse_iterator beginIt = array.rbegin();
			CMyArray<std::string>::const_reverse_iterator endIt = array.rend();
			REQUIRE(endIt - beginIt == 4);
		}

		SECTION("<")
		{
			CMyArray<std::string>::const_reverse_iterator beginIt = array.rbegin();
			CMyArray<std::string>::const_reverse_iterator endIt = array.rend();
			REQUIRE((beginIt < endIt) == true);
			REQUIRE((endIt < beginIt) == false);
			REQUIRE((beginIt < beginIt) == false);
		}

		SECTION(">")
		{
			CMyArray<std::string>::const_reverse_iterator beginIt = array.rbegin();
			CMyArray<std::string>::const_reverse_iterator endIt = array.rend();
			REQUIRE((endIt > beginIt) == true);
			REQUIRE((beginIt > endIt) == false);
			REQUIRE((endIt > endIt) == false);
		}

		SECTION(">=")
		{
			CMyArray<std::string>::const_reverse_iterator beginIt = array.rbegin();
			CMyArray<std::string>::const_reverse_iterator endIt = array.rend();
			REQUIRE((endIt >= beginIt) == true);
			REQUIRE((beginIt >= endIt) == false);
			REQUIRE((beginIt >= beginIt) == true);
		}

		SECTION("<=")
		{
			CMyArray<std::string>::const_reverse_iterator beginIt = array.rbegin();
			CMyArray<std::string>::const_reverse_iterator endIt = array.rend();
			REQUIRE((endIt <= beginIt) == false);
			REQUIRE((beginIt <= endIt) == true);
			REQUIRE((beginIt <= beginIt) == true);
		}

		SECTION("[]")
		{
			CMyArray<std::string>::const_reverse_iterator beginIt = array.rbegin();
			CMyArray<std::string>::const_reverse_iterator endIt = array.rend();
			REQUIRE(beginIt[0] == "!");
		}
	}
}
