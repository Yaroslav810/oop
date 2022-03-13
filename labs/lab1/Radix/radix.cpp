// Radix.cpp : Defines the entry point for the console application.

#include "stdafx.h"

const int MIN_RADIX = 2;
const int MAX_RADIX = 36;

const int MAX_INT = std::numeric_limits<int>::max();
const int MIN_INT = std::numeric_limits<int>::min();

struct Args
{
	int sourceNotation;
	int destinationNotation;
	std::string value;
};

std::string GetString(char ch)
{
	std::string str(1, ch);

	return str;
}

std::string GetString(int n)
{
	return std::to_string(n);
}

std::string BuildOutRangeError(const std::string& source)
{
	return "Invalid <" + source + ">!"
								  "\n"
								  "Use the number system from "
		+ std::to_string(MIN_RADIX) + " to " + std::to_string(MAX_RADIX) + "\n";
}

std::string BuildInvalidArgError(const std::string& source)
{
	return "Invalid value: " + source + "!"
										"\n";
}

std::string BuildInvalidArgcError()
{
	return "Invalid argument count"
		   "\n"
		   "Usage: radix.exe <sourceNotation> <destinationNotation> <value>";
}

std::string buildInvalidValueInNumberSystem(const std::string& str, int radix)
{
	return str + " cannot be in the " + GetString(radix) + " number system";
}

bool IsDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}

bool IsCapitalLetter(char ch)
{
	return ch >= 'A' && ch <= 'Z';
}

int charToInt(char ch)
{
	if (IsDigit(ch))
	{
		return ch - '0';
	}
	if (IsCapitalLetter(ch))
	{
		return ch - 'A' + 10;
	}

	throw std::invalid_argument(BuildInvalidArgError(GetString(ch)));
}

int ConcatenateDigitToNumber(int number, int digit, int radix, bool isNegative)
{
	if (number > (MAX_INT - digit) / radix)
	{
		throw std::out_of_range("Too big a number!");
	}
	if (number < (MIN_INT + digit) / radix)
	{
		throw std::out_of_range("Too small a number!");
	}

	if (isNegative)
	{
		return number * radix - digit;
	}

	return number * radix + digit;
}

int StringToInt(const std::string& str, int radix)
{
	if (str.empty())
	{
		throw std::invalid_argument("Missing number");
	}

	int number = 0;
	bool isNegativeNumber = str[0] == '-';

	for (size_t i = isNegativeNumber ? 1 : 0; i < str.length(); ++i)
	{
		auto digit = charToInt(str[i]);
		if (digit >= radix)
		{
			throw std::invalid_argument(
				BuildInvalidArgError(GetString(str[i])) + buildInvalidValueInNumberSystem(GetString(str[i]), radix));
		}

		number = ConcatenateDigitToNumber(number, digit, radix, isNegativeNumber);
	}

	return number;
}

char IntToChar(int n)
{
	if (n >= 0 && n < 10)
	{
		return static_cast<char>(n + '0');
	}
	if (n >= 10 && n <= MAX_RADIX)
	{
		return static_cast<char>(n - 10 + 'A');
	}

	throw std::invalid_argument(BuildInvalidArgError(GetString(n)));
}

std::string IntToString(int n, int radix)
{
	if (n == 0)
	{
		return "0";
	}

	bool isNegativeNumber = (n < 0);

	std::string result;
	while (n != 0)
	{
		auto div = std::div(n, radix);
		result.push_back(IntToChar(abs(div.rem)));
		n = div.quot;
	}

	if (isNegativeNumber)
	{
		result += '-';
	}

	std::reverse(result.begin(), result.end());

	return result;
}

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		throw std::invalid_argument(BuildInvalidArgcError());
	}

	int sourceNotation = StringToInt(argv[1], 10);
	int destinationNotation = StringToInt(argv[2], 10);
	std::string value = argv[3];

	if (sourceNotation > MAX_RADIX || sourceNotation < MIN_RADIX)
	{
		throw std::out_of_range(BuildOutRangeError("sourceNotation"));
	}

	if (destinationNotation > MAX_RADIX || destinationNotation < MIN_RADIX)
	{
		throw std::out_of_range(BuildOutRangeError("destinationNotation"));
	}

	return {
		.sourceNotation = sourceNotation,
		.destinationNotation = destinationNotation,
		.value = value
	};
}

std::string TranslationNumberFromSourceNumberSystemToDestination(const std::string& value, int sourceNotation, int destinationNotation)
{
	return IntToString(StringToInt(value, sourceNotation), destinationNotation);
}

int main(int argc, char* argv[])
{
	try
	{
		auto data = ParseArgs(argc, argv);
		std::cout << TranslationNumberFromSourceNumberSystemToDestination(
			data.value,
			data.sourceNotation,
			data.destinationNotation);
		std::cout << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
