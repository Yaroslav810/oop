#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../dictionary.h"

TEST_CASE("dictionary")
{
	SECTION("Adding words")
	{
		Dictionary dictionary = {
			{"hello", {"привет"}}
		};

		AddTranslation(dictionary, "buy", "пока");
		REQUIRE(dictionary.size() == 2);
	}
}
