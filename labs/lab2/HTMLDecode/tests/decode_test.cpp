#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../decode.h"

TEST_CASE("html can be decode")
{
	SECTION("Empty data")
	{
		std::istringstream iss;
		std::ostringstream oss;

		CopyStreamWithDecode(iss, oss);
		REQUIRE(oss.str().empty());
	}

	SECTION("There are no replacement literals in the string")
	{
		std::istringstream iss("There are no replacement literals in the string\n");
		std::ostringstream oss;

		CopyStreamWithDecode(iss, oss);
		REQUIRE(oss.str() == "There are no replacement literals in the string\n");
	}

	SECTION("A string of only one replacement")
	{
		std::istringstream iss("&lt;\n");
		std::ostringstream oss;

		CopyStreamWithDecode(iss, oss);
		REQUIRE(oss.str() == "<\n");
	}

	SECTION("String without substitutions")
	{
		std::istringstream iss("&lt\n");
		std::ostringstream oss;

		CopyStreamWithDecode(iss, oss);
		REQUIRE(oss.str() == "&lt\n");
	}

	SECTION("Replacing multiple literals")
	{
		std::istringstream iss("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s\n");
		std::ostringstream oss;

		CopyStreamWithDecode(iss, oss);
		REQUIRE(oss.str() == "Cat <says> \"Meow\". M&M's\n");
	}

	SECTION("A few lines")
	{
		std::istringstream iss("Cat\n&lt;says&gt;\n&quot;Meow\n&quot;.\nM&amp;\nM&apos;s\n");
		std::ostringstream oss;

		CopyStreamWithDecode(iss, oss);
		REQUIRE(oss.str() == "Cat\n<says>\n\"Meow\n\".\nM&\nM's\n");
	}

	SECTION("String of ampersands")
	{
		std::istringstream iss("&&&&&&&&&&&&&&&&&&&&&\n");
		std::ostringstream oss;

		CopyStreamWithDecode(iss, oss);
		REQUIRE(oss.str() == "&&&&&&&&&&&&&&&&&&&&&\n");
	}

	// TODO: Добавить "&none;" и "&amp;lt;"
	SECTION("No section")
	{
		std::istringstream iss("&none;\n");
		std::ostringstream oss;

		CopyStreamWithDecode(iss, oss);
		REQUIRE(oss.str() == "&none;\n");
	}
	SECTION("Missing ampersand - without replacement")
	{
		std::istringstream iss("&amp;lt;\n");
		std::ostringstream oss;

		CopyStreamWithDecode(iss, oss);
		REQUIRE(oss.str() == "&lt;\n");
	}
}
