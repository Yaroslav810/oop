#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../CMyString.h"

TEST_CASE("Creating CMyString")
{
	SECTION("Empty constructor")
	{
		CMyString string;
		REQUIRE(std::strcmp(string.GetStringData(), "") == 0);
		REQUIRE(string.GetLength() == 0);
	}

	SECTION("Pointer on char")
	{
		SECTION("Pointer on empty")
		{
			CMyString string("");
			REQUIRE(std::strcmp(string.GetStringData(), "") == 0);
			REQUIRE(string.GetLength() == 0);
		}

		SECTION("Pointer on 123")
		{
			CMyString string("123");
			REQUIRE(std::strcmp(string.GetStringData(), "123") == 0);
			REQUIRE(string.GetLength() == 3);
		}

		SECTION("Pointer on nullptr")
		{
			CMyString string(nullptr);
			REQUIRE(std::strcmp(string.GetStringData(), "") == 0);
			REQUIRE(string.GetLength() == 0);
		}
	}

	SECTION("Pointer on char and length")
	{
		SECTION("Pointer on empty and length = 0")
		{
			CMyString string("", 0);
			REQUIRE(std::strcmp(string.GetStringData(), "") == 0);
			REQUIRE(string.GetLength() == 0);
		}

		SECTION("Pointer on empty and length = 10")
		{
			CMyString string("", 10);
			REQUIRE(std::strcmp(string.GetStringData(), "") == 0);
			REQUIRE(string.GetLength() == 10);
		}

		SECTION("Pointer on 'Hello, world' and length = 5")
		{
			CMyString string("Hello, world", 5);
			REQUIRE(std::strcmp(string.GetStringData(), "Hello") == 0);
			REQUIRE(string.GetLength() == 5);
		}

		SECTION("Pointer on 'Hello' and length = 5")
		{
			CMyString string("Hello", 5);
			REQUIRE(std::strcmp(string.GetStringData(), "Hello") == 0);
			REQUIRE(string.GetLength() == 5);
		}

		SECTION("Pointer on nullptr and length = 5")
		{
			CMyString string(nullptr, 5);
			REQUIRE(std::strcmp(string.GetStringData(), "") == 0);
			REQUIRE(string.GetLength() == 0);
		}
	}

	SECTION("STL string")
	{
		SECTION("Empty string")
		{
			std::string str;
			CMyString string(str);
			REQUIRE(std::strcmp(string.GetStringData(), "") == 0);
			REQUIRE(string.GetLength() == 0);
		}

		SECTION("String with 'Hello'")
		{
			std::string str = "Hello";
			CMyString string(str);
			REQUIRE(std::strcmp(string.GetStringData(), "Hello") == 0);
			REQUIRE(string.GetLength() == 5);
		}
	}
}

TEST_CASE("Copying constructor")
{
	SECTION("Successful object creation")
	{
		CMyString str1 = "Hello, world";
		CMyString str2(str1);
		REQUIRE(std::strcmp(str1.GetStringData(), str2.GetStringData()) == 0);
		REQUIRE(str1.GetLength() == str2.GetLength());
	}

	SECTION("Creating a new object")
	{
		CMyString str1 = "Hello, world";
		CMyString str2(str1);
		str1 += "!";
		REQUIRE(std::strcmp(str1.GetStringData(), "Hello, world!") == 0);
		REQUIRE(std::strcmp(str2.GetStringData(), "Hello, world") == 0);
		REQUIRE(str1.GetLength() == 13);
		REQUIRE(str2.GetLength() == 12);
	}
}

TEST_CASE("Moving constructor")
{
	SECTION("Successful object moving")
	{
		CMyString str1 = "Hello, world";
		CMyString str2(std::move(str1));
		REQUIRE(str1.GetStringData() == nullptr);
		REQUIRE(std::strcmp(str2.GetStringData(), "Hello, world") == 0);
		REQUIRE(str1.GetLength() == 0);
		REQUIRE(str2.GetLength() == 12);
	}
}

TEST_CASE("Substring")
{
	SECTION("Restriction within a string")
	{
		CMyString str = "Hello, world";
		CMyString result = str.SubString(0, 5);
		REQUIRE(std::strcmp(result.GetStringData(), "Hello") == 0);
		REQUIRE(result.GetLength() == 5);
	}

	SECTION("Until the end")
	{
		CMyString str = "Hello, world";
		CMyString result = str.SubString(7);
		REQUIRE(std::strcmp(result.GetStringData(), "world") == 0);
		REQUIRE(result.GetLength() == 5);
	}

	SECTION("End after")
	{
		CMyString str = "Hello, world";
		CMyString result = str.SubString(7, 10);
		REQUIRE(std::strcmp(result.GetStringData(), "world") == 0);
		REQUIRE(result.GetLength() == 5);
	}

	SECTION("Start after")
	{
		CMyString str = "Hello, world";
		CMyString result = str.SubString(50);
		REQUIRE(std::strcmp(result.GetStringData(), "") == 0);
	}
}

TEST_CASE("Clear")
{
	SECTION("Empty string")
	{
		CMyString str;
		str.Clear();
		REQUIRE(std::strcmp(str.GetStringData(), "") == 0);
		REQUIRE(str.GetLength() == 0);
	}

	SECTION("String with 'Hello, world'")
	{
		CMyString str("Hello, world!");
		str.Clear();
		REQUIRE(std::strcmp(str.GetStringData(), "") == 0);
		REQUIRE(str.GetLength() == 0);
	}
}

TEST_CASE("String assignment")
{
	SECTION("Copying")
	{
		CMyString str1 = "Hello, world";
		CMyString str2;
		str2 = str1;

		REQUIRE(std::strcmp(str1.GetStringData(), "Hello, world") == 0);
		REQUIRE(std::strcmp(str2.GetStringData(), "Hello, world") == 0);
		REQUIRE(str1.GetLength() == 12);
		REQUIRE(str2.GetLength() == 12);
	}

	SECTION("Moving")
	{
		CMyString str1 = "Hello, world";
		CMyString str2;
		str2 = std::move(str1);

		REQUIRE(str1.GetStringData() == nullptr);
		REQUIRE(std::strcmp(str2.GetStringData(), "Hello, world") == 0);
		REQUIRE(str1.GetLength() == 0);
		REQUIRE(str2.GetLength() == 12);
	}

	SECTION("Self copying")
	{
		CMyString str = "Hello, world";
		str = str;

		REQUIRE(std::strcmp(str.GetStringData(), "Hello, world") == 0);
		REQUIRE(str.GetLength() == 12);
	}

	SECTION("Self moving")
	{
		CMyString str = "Hello, world";
		str = std::move(str);

		REQUIRE(std::strcmp(str.GetStringData(), "Hello, world") == 0);
		REQUIRE(str.GetLength() == 12);
	}
}

TEST_CASE("Indexing")
{
	SECTION("Reading")
	{
		CMyString str = "Hello, world";
		REQUIRE(str[2] == 'l');
	}

	SECTION("Writing")
	{
		CMyString str = "Hello, world";
		str[5] = '.';
		REQUIRE(std::strcmp(str.GetStringData(), "Hello. world") == 0);
	}

	SECTION("Going beyond")
	{
		CMyString str = "Hello, world";
		REQUIRE_THROWS_AS(str[50], std::out_of_range);
		REQUIRE_THROWS_AS(str[50] = 'W', std::out_of_range);
	}
}

TEST_CASE("+-")
{
	SECTION("'Hello,' + 'world' => 'Hello, world'")
	{
		CMyString str1 = "Hello, ";
		CMyString str2 = "world";
		str1 += str2;
		REQUIRE(std::strcmp(str1.GetStringData(), "Hello, world") == 0);
		REQUIRE(str1.GetLength() == 12);
		REQUIRE(std::strcmp(str2.GetStringData(), "world") == 0);
		REQUIRE(str2.GetLength() == 5);
	}

	SECTION("'' + 'world' => 'Hello, world'")
	{
		CMyString str1;
		CMyString str2 = "world";
		str1 += str2;
		REQUIRE(std::strcmp(str1.GetStringData(), "world") == 0);
		REQUIRE(str1.GetLength() == 5);
		REQUIRE(std::strcmp(str2.GetStringData(), "world") == 0);
		REQUIRE(str2.GetLength() == 5);
	}

	SECTION("'Hello' + '' => 'Hello'")
	{
		CMyString str1 = "Hello";
		CMyString str2;
		str1 += str2;
		REQUIRE(std::strcmp(str1.GetStringData(), "Hello") == 0);
		REQUIRE(str1.GetLength() == 5);
	}
}

TEST_CASE("+")
{
	SECTION("'Hello,' + 'world' => 'Hello, world'")
	{
		CMyString str1 = "Hello, ";
		CMyString str2 = "world";
		CMyString result = str1 + str2;
		REQUIRE(std::strcmp(str1.GetStringData(), "Hello, ") == 0);
		REQUIRE(str1.GetLength() == 7);
		REQUIRE(std::strcmp(str2.GetStringData(), "world") == 0);
		REQUIRE(str2.GetLength() == 5);
		REQUIRE(std::strcmp(result.GetStringData(), "Hello, world") == 0);
		REQUIRE(result.GetLength() == 12);
	}

	SECTION("The same variable")
	{
		CMyString str = "Hello";
		CMyString result = str + str;
		REQUIRE(std::strcmp(str.GetStringData(), "Hello") == 0);
		REQUIRE(str.GetLength() == 5);
		REQUIRE(std::strcmp(result.GetStringData(), "HelloHello") == 0);
		REQUIRE(result.GetLength() == 10);
	}

	SECTION("One variable")
	{
		CMyString str = "Hello";
		str = str + str;
		REQUIRE(std::strcmp(str.GetStringData(), "HelloHello") == 0);
		REQUIRE(str.GetLength() == 10);
	}
}

TEST_CASE("==")
{
	SECTION("'Hello' == 'Hello' => true")
	{
		CMyString str1 = "Hello";
		CMyString str2 = "Hello";
		REQUIRE((str1 == str2) == true);
	}

	SECTION("'Hello' == 'World' => false")
	{
		CMyString str1 = "Hello";
		CMyString str2 = "World";
		REQUIRE((str1 == str2) == false);
	}
}

TEST_CASE("!=")
{
	SECTION("'Hello' != 'Hello' => false")
	{
		CMyString str1 = "Hello";
		CMyString str2 = "Hello";
		REQUIRE((str1 != str2) == false);
	}

	SECTION("'Hello' != 'World' => true")
	{
		CMyString str1 = "Hello";
		CMyString str2 = "World";
		REQUIRE((str1 != str2) == true);
	}
}

TEST_CASE("<")
{
	SECTION("'12' < '12' => false")
	{
		CMyString str1 = "12";
		CMyString str2 = "12";
		REQUIRE((str1 < str2) == false);
	}

	SECTION("'123' < '12' => false")
	{
		CMyString str1 = "123";
		CMyString str2 = "12";
		REQUIRE((str1 < str2) == false);
	}

	SECTION("'12' < '123' => true")
	{
		CMyString str1 = "12";
		CMyString str2 = "123";
		REQUIRE((str1 < str2) == true);
	}
}

TEST_CASE(">")
{
	SECTION("'12' > '12' => false")
	{
		CMyString str1 = "12";
		CMyString str2 = "12";
		REQUIRE((str1 > str2) == false);
	}

	SECTION("'123' > '12' => true")
	{
		CMyString str1 = "123";
		CMyString str2 = "12";
		REQUIRE((str1 > str2) == true);
	}

	SECTION("'12' > '123' => false")
	{
		CMyString str1 = "12";
		CMyString str2 = "123";
		REQUIRE((str1 > str2) == false);
	}
}

TEST_CASE("<=")
{
	SECTION("'12' <= '12' => true")
	{
		CMyString str1 = "12";
		CMyString str2 = "12";
		REQUIRE((str1 <= str2) == true);
	}

	SECTION("'123' <= '12' => false")
	{
		CMyString str1 = "123";
		CMyString str2 = "12";
		REQUIRE((str1 <= str2) == false);
	}

	SECTION("'12' <= '123' => true")
	{
		CMyString str1 = "12";
		CMyString str2 = "123";
		REQUIRE((str1 <= str2) == true);
	}
}

TEST_CASE(">=")
{
	SECTION("'12' >= '12' => true")
	{
		CMyString str1 = "12";
		CMyString str2 = "12";
		REQUIRE((str1 >= str2) == true);
	}

	SECTION("'123' >= '12' => true")
	{
		CMyString str1 = "123";
		CMyString str2 = "12";
		REQUIRE((str1 >= str2) == true);
	}

	SECTION("'12' >= '123' => false")
	{
		CMyString str1 = "12";
		CMyString str2 = "123";
		REQUIRE((str1 >= str2) == false);
	}
}

TEST_CASE("Writing to a stream")
{
	SECTION("Writing 'Hello, world'")
	{
		std::stringstream ss;
		CMyString str("Hello, world");
		ss << str;
		REQUIRE(ss.str() == "Hello, world");
	}
}
