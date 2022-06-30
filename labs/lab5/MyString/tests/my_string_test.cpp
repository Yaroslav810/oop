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
		REQUIRE(str1.GetStringData() == CMyString::GetDefaultString());
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

		REQUIRE(str1.GetStringData() == CMyString::GetDefaultString());
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

TEST_CASE("String const iterator")
{
	SECTION("begin")
	{
		const CMyString str("Hello, world");
		const char* firstPtr = str.GetStringData();
		CMyString::const_iterator it = str.begin();
		REQUIRE(it == firstPtr);
	}

	SECTION("end")
	{
		const CMyString str("Hello, world");
		CMyString::const_iterator it = str.end();
		const char* firstPtr = str.GetStringData();
		REQUIRE(it == firstPtr + str.GetLength());
	}
}

TEST_CASE("String iterator")
{
	SECTION("begin")
	{
		CMyString str("Hello, world");
		char* firstPtr = const_cast<char*>(str.GetStringData());
		CMyString::iterator it = str.begin();
		REQUIRE(it == firstPtr);
	}

	SECTION("end")
	{
		CMyString str("Hello, world");
		CMyString::iterator it = str.end();
		char* firstPtr = const_cast<char*>(str.GetStringData());
		REQUIRE(it == firstPtr + str.GetLength());
	}
}

TEST_CASE("String reverse const iterator")
{
	SECTION("loop")
	{
		std::stringstream ss;
		const CMyString str("Hello");
		for (auto it = str.rbegin(); it != str.rend(); ++it)
		{
			ss << *it;
		}
		REQUIRE(std::memcmp(ss.str().c_str(), "olleH", 5) == 0);
	}
}

TEST_CASE("String reverse iterator")
{
	SECTION("loop")
	{
		std::stringstream ss;
		CMyString str("Hello");
		for (auto it = str.rbegin(); it != str.rend(); ++it)
		{
			ss << *it;
		}
		REQUIRE(std::memcmp(ss.str().c_str(), "olleH", 5) == 0);
	}
}

TEST_CASE("Operation *")
{
	SECTION("iterator")
	{
		CMyString str("Hello, world");
		CMyString::iterator beginIt = str.begin();
		CMyString::iterator endIt = str.end();
		REQUIRE(*beginIt == 'H');
		REQUIRE(*(endIt - 1) == 'd');
		REQUIRE(*endIt == '\0');
	}

	SECTION("const iterator")
	{
		const CMyString str("Hello, world");
		CMyString::const_iterator beginIt = str.begin();
		CMyString::const_iterator endIt = str.end();
		REQUIRE(*beginIt == 'H');
		REQUIRE(*(endIt - 1) == 'd');
		REQUIRE(*endIt == '\0');
	}

	SECTION("reverse iterator")
	{
		CMyString str("Hello, world");
		CMyString::reverse_iterator rbeginIt = str.rbegin();
		CMyString::reverse_iterator rendIt = str.rend();
		REQUIRE(*rbeginIt == 'd');
		REQUIRE(*(rendIt - 1) == 'H');
	}

	SECTION("const reverse iterator")
	{
		const CMyString str("Hello, world");
		CMyString::const_reverse_iterator rbeginIt = str.rbegin();
		CMyString::const_reverse_iterator rendIt = str.rend();
		REQUIRE(*rbeginIt == 'd');
		REQUIRE(*(rendIt - 1) == 'H');
	}
}

TEST_CASE("pre ++")
{
	SECTION("const iterator")
	{
		const CMyString str("World");
		CMyString::const_iterator it = str.begin();
		REQUIRE(*it == 'W');
		REQUIRE(*(++it) == 'o');
		REQUIRE(*it == 'o');
	}

	SECTION("iterator")
	{
		CMyString str("World");
		CMyString::iterator it = str.begin();
		REQUIRE(*it == 'W');
		REQUIRE(*(++it) == 'o');
		REQUIRE(*it == 'o');
	}

	SECTION("const reverse iterator")
	{
		const CMyString str("World");
		CMyString::const_reverse_iterator it = str.rbegin();
		REQUIRE(*it == 'd');
		REQUIRE(*(++it) == 'l');
		REQUIRE(*it == 'l');
	}

	SECTION("reverse iterator")
	{
		CMyString str("World");
		CMyString::reverse_iterator it = str.rbegin();
		REQUIRE(*it == 'd');
		REQUIRE(*(++it) == 'l');
		REQUIRE(*it == 'l');
	}
}

TEST_CASE("Another operation")
{
	SECTION("post ++")
	{
		const CMyString str("World");
		CMyString::const_iterator it = str.begin();
		REQUIRE(*it == 'W');
		REQUIRE(*(it++) == 'W');
		REQUIRE(*it == 'o');
	}

	SECTION("pre --")
	{
		const CMyString str("World");
		CMyString::const_iterator it = str.end();
		REQUIRE(*it == '\0');
		REQUIRE(*(--it) == 'd');
		REQUIRE(*it == 'd');
	}

	SECTION("post --")
	{
		const CMyString str("World");
		CMyString::const_iterator it = str.end();
		REQUIRE(*it == '\0');
		REQUIRE(*(it--) == '\0');
		REQUIRE(*it == 'd');
	}

	SECTION("+=")
	{
		const CMyString str("Hello, world");
		CMyString::const_iterator it = str.begin();
		REQUIRE(*it == 'H');
		it += 1;
		REQUIRE(*it == 'e');
		it += 3;
		REQUIRE(*it == 'o');
	}

	SECTION("-=")
	{
		const CMyString str("Hello, world");
		CMyString::const_iterator it = str.end();
		REQUIRE(*it == '\0');
		it -= 1;
		REQUIRE(*it == 'd');
		it -= 2;
		REQUIRE(*it == 'r');
	}

	SECTION("+")
	{
		const CMyString str("Hello, world");
		CMyString::const_iterator it = str.begin();
		REQUIRE(*it == 'H');
		it = it + 1;
		REQUIRE(*it == 'e');
		it = it + 3;
		REQUIRE(*it == 'o');
	}

	SECTION("+")
	{
		const CMyString str("Hello, world");
		CMyString::const_iterator it = str.begin();
		REQUIRE(*it == 'H');
		it = 1 + it;
		REQUIRE(*it == 'e');
		it = 3 + it;
		REQUIRE(*it == 'o');
	}

	SECTION("-")
	{
		const CMyString str("Hello, world");
		CMyString::const_iterator it = str.end();
		REQUIRE(*it == '\0');
		it = it - 1;
		REQUIRE(*it == 'd');
		it = it - 2;
		REQUIRE(*it == 'r');
	}

	SECTION("- iterators")
	{
		const CMyString str("Hello, world");
		CMyString::const_iterator beginIt = str.begin();
		CMyString::const_iterator endIt = str.end();
		REQUIRE(endIt - beginIt == 12);
		beginIt++;
		endIt--;
		REQUIRE(endIt - beginIt == 10);
	}

	SECTION("<")
	{
		const CMyString str("Hello, world");
		CMyString::const_iterator beginIt = str.begin();
		CMyString::const_iterator endIt = str.end();
		REQUIRE((beginIt < endIt) == true);
		REQUIRE((endIt < beginIt) == false);
		beginIt += str.GetLength();
		REQUIRE((beginIt < endIt) == false);
	}

	SECTION(">")
	{
		const CMyString str("Hello, world");
		CMyString::const_iterator beginIt = str.begin();
		CMyString::const_iterator endIt = str.end();
		REQUIRE((beginIt > endIt) == false);
		REQUIRE((endIt > beginIt) == true);
		beginIt += str.GetLength();
		REQUIRE((endIt > beginIt) == false);
	}

	SECTION("<=")
	{
		const CMyString str("Hello, world");
		CMyString::const_iterator beginIt = str.begin();
		CMyString::const_iterator endIt = str.end();
		REQUIRE((beginIt <= endIt) == true);
		REQUIRE((endIt <= beginIt) == false);
		beginIt += str.GetLength();
		REQUIRE((beginIt <= endIt) == true);
	}

	SECTION(">=")
	{
		const CMyString str("Hello, world");
		CMyString::const_iterator beginIt = str.begin();
		CMyString::const_iterator endIt = str.end();
		REQUIRE((beginIt >= endIt) == false);
		REQUIRE((endIt >= beginIt) == true);
		beginIt += str.GetLength();
		REQUIRE((endIt >= beginIt) == true);
	}

	SECTION("[]")
	{
		const CMyString str("Hello, world");
		CMyString::const_iterator it = str.begin();
		REQUIRE(it[0] == 'H');
		REQUIRE(it[1] == 'e');
		REQUIRE(it[2] == 'l');
		it += str.GetLength();
		REQUIRE(it[0] == '\0');
		REQUIRE(it[-1] == 'd');
		REQUIRE(it[-2] == 'l');
	}
}

TEST_CASE("range based")
{
	SECTION("reference")
	{
		std::stringstream ss;
		CMyString str("Hello, world");
		for (char& ch : str)
		{
			ss << ch;
		}

		REQUIRE(ss.str() == "Hello, world");
	}

	SECTION("iterator")
	{
		std::stringstream ss;
		CMyString str("Hello, world");
		CMyString::iterator endIt = str.end();
		for (auto it = str.begin(); it != endIt; it++)
		{
			ss << *it;
		}

		REQUIRE(ss.str() == "Hello, world");
	}
}
