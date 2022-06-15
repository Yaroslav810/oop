#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../CHttpUrl.h"

TEST_CASE("Creating a CHttpUrl")
{
	SECTION("Constructor with string parsing")
	{
		SECTION("https://yandex.ru:1000/images/search")
		{
			CHttpUrl url("https://yandex.ru:1000/images/search");
			REQUIRE(url.GetDomain() == "yandex.ru");
			REQUIRE(url.GetDocument() == "/images/search");
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetPort() == 1000);
		}

		SECTION("https://yandex.ru/images/search")
		{
			CHttpUrl url("https://yandex.ru/images/search");
			REQUIRE(url.GetDomain() == "yandex.ru");
			REQUIRE(url.GetDocument() == "/images/search");
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetPort() == 443);
		}

		SECTION("http://yandex.ru:1000/images/search")
		{
			CHttpUrl url("http://yandex.ru:1000/images/search");
			REQUIRE(url.GetDomain() == "yandex.ru");
			REQUIRE(url.GetDocument() == "/images/search");
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTP);
			REQUIRE(url.GetPort() == 1000);
		}

		SECTION("http://yandex.ru/images/search")
		{
			CHttpUrl url("http://yandex.ru/images/search");
			REQUIRE(url.GetDomain() == "yandex.ru");
			REQUIRE(url.GetDocument() == "/images/search");
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTP);
			REQUIRE(url.GetPort() == 80);
		}

		SECTION("https://yandex.ru:1000")
		{
			CHttpUrl url("https://yandex.ru:1000");
			REQUIRE(url.GetDomain() == "yandex.ru");
			REQUIRE(url.GetDocument() == "/");
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetPort() == 1000);
		}

		SECTION("https://yandex.ru")
		{
			CHttpUrl url("https://yandex.ru");
			REQUIRE(url.GetDomain() == "yandex.ru");
			REQUIRE(url.GetDocument() == "/");
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetPort() == 443);
		}

		SECTION("https://yandex.ru:1/images/search")
		{
			CHttpUrl url("https://yandex.ru:1/images/search");
			REQUIRE(url.GetDomain() == "yandex.ru");
			REQUIRE(url.GetDocument() == "/images/search");
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetPort() == 1);
		}

		SECTION("https://yandex.ru:65535/images/search")
		{
			CHttpUrl url("https://yandex.ru:65535/images/search");
			REQUIRE(url.GetDomain() == "yandex.ru");
			REQUIRE(url.GetDocument() == "/images/search");
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetPort() == 65535);
		}

		SECTION("HTTPS://YANDEX.RU:1000/IMAGES/SEARCH")
		{
			CHttpUrl url("HTTPS://yandex.ru:1000/images/search");
			REQUIRE(url.GetDomain() == "yandex.ru");
			REQUIRE(url.GetDocument() == "/images/search");
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetPort() == 1000);
		}
	}

	SECTION("Constructor without a port")
	{
		SECTION("https://yandex.ru/images/search")
		{
			CHttpUrl url(
				"yandex.ru",
				"/images/search",
				CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetDomain() == "yandex.ru");
			REQUIRE(url.GetDocument() == "/images/search");
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetPort() == 443);
		}

		SECTION("http://yandex.ru/images/search")
		{
			CHttpUrl url(
				"yandex.ru",
				"/images/search",
				CHttpUrl::Protocol::HTTP);
			REQUIRE(url.GetDomain() == "yandex.ru");
			REQUIRE(url.GetDocument() == "/images/search");
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTP);
			REQUIRE(url.GetPort() == 80);
		}

		SECTION("https://yandex.ru")
		{
			CHttpUrl url(
				"yandex.ru",
				"",
				CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetDomain() == "yandex.ru");
			REQUIRE(url.GetDocument() == "/");
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetPort() == 443);
		}

		SECTION("https://yandex.ru/images/search")
		{
			CHttpUrl url(
				"yandex.ru",
				"images/search",
				CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetDomain() == "yandex.ru");
			REQUIRE(url.GetDocument() == "/images/search");
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetPort() == 443);
		}
	}

	SECTION("Constructor with port")
	{
		SECTION("https://yandex.ru:1000/images/search")
		{
			CHttpUrl url(
				"yandex.ru",
				"/images/search",
				CHttpUrl::Protocol::HTTPS,
				1000);
			REQUIRE(url.GetDomain() == "yandex.ru");
			REQUIRE(url.GetDocument() == "/images/search");
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetPort() == 1000);
		}

		SECTION("https://yandex.ru:1000")
		{
			CHttpUrl url(
				"yandex.ru",
				"",
				CHttpUrl::Protocol::HTTPS,
				1000);
			REQUIRE(url.GetDomain() == "yandex.ru");
			REQUIRE(url.GetDocument() == "/");
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetPort() == 1000);
		}

		SECTION("http://yandex.ru:1000/images/search")
		{
			CHttpUrl url(
				"yandex.ru",
				"/images/search",
				CHttpUrl::Protocol::HTTP,
				1000);
			REQUIRE(url.GetDomain() == "yandex.ru");
			REQUIRE(url.GetDocument() == "/images/search");
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTP);
			REQUIRE(url.GetPort() == 1000);
		}

		SECTION("https://yandex.ru:1000/images/search")
		{
			CHttpUrl url(
				"yandex.ru",
				"images/search",
				CHttpUrl::Protocol::HTTPS,
				1000);
			REQUIRE(url.GetDomain() == "yandex.ru");
			REQUIRE(url.GetDocument() == "/images/search");
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetPort() == 1000);
		}
	}
}

TEST_CASE("Error")
{
	SECTION("Empty")
	{
		REQUIRE_THROWS_AS(CHttpUrl(""), CUrlParsingError);
	}

	SECTION("yaroslav@mail.ru")
	{
		REQUIRE_THROWS_AS(CHttpUrl("yaroslav@mail.ru"), CUrlParsingError);
	}

	SECTION("https:///domain")
	{
		REQUIRE_THROWS_AS(CHttpUrl("https:///domain.ru"), CUrlParsingError);
	}

	SECTION("https::/domain")
	{
		REQUIRE_THROWS_AS(CHttpUrl("https::/domain.ru"), CUrlParsingError);
	}

	SECTION("https:80")
	{
		REQUIRE_THROWS_AS(CHttpUrl("https:80"), CUrlParsingError);
	}

	SECTION("Invalid port")
	{
		REQUIRE_THROWS_AS(CHttpUrl("https://yandex.ru:-1"), CUrlParsingError);
		REQUIRE_THROWS_AS(CHttpUrl("https://yandex.ru:0"), CUrlParsingError);
		REQUIRE_THROWS_AS(CHttpUrl("https://yandex.ru:65536"), CUrlParsingError);
	}
}

TEST_CASE("String from protocol")
{
	SECTION("Http")
	{
		REQUIRE(CHttpUrl::GetStringFromProtocol(CHttpUrl::Protocol::HTTP) == "http");
	}

	SECTION("Https")
	{
		REQUIRE(CHttpUrl::GetStringFromProtocol(CHttpUrl::Protocol::HTTPS) == "https");
	}
}
