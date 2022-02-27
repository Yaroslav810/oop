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

std::string getString(const char& ch)
{
    std::string str(1, ch);

    return str;
}

std::string getString(const int& n)
{
    return std::to_string(n);
}

std::string buildOutRangeError(const std::string& source)
{
    return "Invalid <" + source + ">!" "\n" "Use the number system from " + std::to_string(MIN_RADIX) + " to " + std::to_string(MAX_RADIX) + "\n";
}

std::string buildInvalidArgError(const std::string& source)
{
    return "Invalid value: " + source + "!" "\n";
}

std::string buildInvalidArgcError()
{
    return "Invalid argument count" "\n" "Usage: radix.exe <sourceNotation> <destinationNotation> <value>";
}

std::string buildInvalidValueInNumberSystem(const std::string& str, int& radix)
{
    return str + " cannot be in the " + getString(radix) + " number system";
}

Args parseArgs(int argc, char* argv[])
{
    if (argc != 4)
    {
        throw std::invalid_argument(buildInvalidArgcError());
    }

    int sourceNotation = std::strtol(argv[1], nullptr, 10);
    int destinationNotation = std::strtol(argv[2], nullptr, 10);
    std::string value = argv[3];

    if (sourceNotation > MAX_RADIX || sourceNotation < MIN_RADIX)
    {
        throw std::out_of_range(buildOutRangeError("sourceNotation"));
    }

    if (destinationNotation > MAX_RADIX || destinationNotation < MIN_RADIX)
    {
        throw std::out_of_range(buildOutRangeError("destinationNotation"));
    }

    return
    {
        .sourceNotation = sourceNotation,
        .destinationNotation = destinationNotation,
        .value = value
    };
}

bool isDigit(const char& ch)
{
    return ch >= '0' && ch <= '9';
}

bool isLetter(const char& ch)
{
    return ch >= 'A' && ch <= 'Z';
}

int charToInt(const char& ch)
{
    if (isDigit(ch))
    {
        return ch - '0';
    }
    if (isLetter(ch))
    {
        return ch - 'A' + 10;
    }

    throw std::invalid_argument(buildInvalidArgError(getString(ch)));
}

int updateNumber(const int& number, const int& radix, const int& digit, const bool& isNegative)
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

int stringToInt(const std::string& str, int radix)
{
    if (str.empty())
    {
        throw std::invalid_argument("Missing number");
    }

    int decimalNumber = 0;
    bool isNegativeNumber = str[0] == '-';

    for (int i = isNegativeNumber ? 1 : 0; i < str.length(); ++i)
    {
        auto number = charToInt(str[i]);
        if (number >= radix)
        {
            throw std::invalid_argument(
                    buildInvalidArgError(getString(str[i])) +
                    buildInvalidValueInNumberSystem(getString(str[i]), radix));
        }

        decimalNumber = updateNumber(decimalNumber, radix, number, isNegativeNumber);
    }

    return decimalNumber;
}

char intToChar(const int& n)
{
    if (n >= 0 && n < 10)
    {
        return static_cast<char>(n + '0');
    }
    if (n >= 10 && n <= 36)
    {
        return static_cast<char>(n - 10 + 'A');
    }

    throw std::invalid_argument(buildInvalidArgError(getString(n)));
}

std::string intToString(int n, int radix)
{
    if (n == 0)
    {
        return "0";
    }

    bool isNegativeNumber = (n < 0);

    std::string result;
    while (n != 0)
    {
        auto remains = n % radix;
        if (remains < 0)
        {
            remains *= -1;
        }
        result.push_back(intToChar(remains));
        n /= radix;
    }

    if (isNegativeNumber)
    {
        result += '-';
    }

    std::reverse(result.begin(), result.end());

    return result;
}

int main(int argc, char* argv[])
{
    try
    {
        auto data = parseArgs(argc, argv);

        std::cout << intToString(stringToInt(data.value, data.sourceNotation), data.destinationNotation) << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
