#include "stdafx.h"

const int MIN_KEY = 0;
const int MAX_KEY = 255;

const std::string CRYPT_MODE = "crypt";
const std::string DECRYPT_MODE = "decrypt";

const int MAX_INT = std::numeric_limits<int>::max();
const int MIN_INT = std::numeric_limits<int>::min();

enum class Mode
{
	CRYPT,
	DECRYPT,
};

struct Args
{
	Mode mode;
	std::string input;
	std::string output;
	unsigned char key;
};

std::string getString(const int& n)
{
	return std::to_string(n);
}

std::string buildInvalidArgcError()
{
	return "Invalid argument count"
		   "\n"
		   "Usage:"
		   "\n"
		   "     - crypt.exe crypt <inputFile> <outputFile> <key> for crypt"
		   "\n"
		   "     - crypt.exe decrypt <inputFile> <outputFile> <key> for decrypt";
}

std::string buildInvalidModeError(const std::string& str)
{
	return "Failed to recognize the mode!"
		   "\n"
		   "Expected <"
		+ CRYPT_MODE + "> or <" + DECRYPT_MODE + ">, but received: " + str + "\n";
}

std::string buildInvalidKeyError(const std::string& str)
{
	return "Invalid key!"
		   "\n"
		   "Use a number from "
		+ getString(MIN_KEY) + " to " + getString(MAX_KEY) + "\n";
}

std::string buildFileReadingError()
{
	return "Error reading the file!"
		   "\n"
		   "It is possible that the file is corrupted or there are no permissions to read it"
		   "\n";
}

std::string buildFileWritingError()
{
	return "Error writing the file!"
		   "\n"
		   "It is possible that the file is corrupted or there are no permissions to write it"
		   "\n";
}

std::string buildInvalidNumberSystemError()
{
	return "To indicate the key, use the decimal system of reading!"
		   "\n";
}

Mode parseMode(const std::string& mode)
{
	if (mode == CRYPT_MODE)
	{
		return Mode::CRYPT;
	}
	if (mode == DECRYPT_MODE)
	{
		return Mode::DECRYPT;
	}

	throw std::invalid_argument(buildInvalidModeError(mode));
}

int charToDigit(const char& ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return ch - '0';
	}

	throw std::invalid_argument(buildInvalidNumberSystemError());
}

int updateNumber(const int& number, const int& digit, const bool& isNegative)
{
	if (number > (MAX_INT - digit) / 10)
	{
		throw std::out_of_range("Too big a number!");
	}
	if (number < (MIN_INT + digit) / 10)
	{
		throw std::out_of_range("Too small a number!");
	}

	if (isNegative)
	{
		return number * 10 - digit;
	}

	return number * 10 + digit;
}

int stringToInt(const std::string& str)
{
	if (str.empty())
	{
		throw std::invalid_argument("Missing number");
	}

	int decimalNumber = 0;
	bool isNegativeNumber = str[0] == '-';

	for (int i = isNegativeNumber ? 1 : 0; i < str.length(); ++i)
	{
		auto number = charToDigit(str[i]);

		decimalNumber = updateNumber(decimalNumber, number, isNegativeNumber);
	}

	return decimalNumber;
}

unsigned char parseKey(const std::string& key)
{
	auto number = stringToInt(key);
	if (number < MIN_KEY || number > MAX_KEY)
	{
		throw std::invalid_argument(buildInvalidKeyError(key));
	}

	return static_cast<unsigned char>(number);
}

Args parseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::invalid_argument(buildInvalidArgcError());
	}

	return {
		.mode = parseMode(argv[1]),
		.input = argv[2],
		.output = argv[3],
		.key = parseKey(argv[4]),
	};
}

void encrypt(char& byte, const unsigned char& key)
{
	byte ^= key;

	byte = ((byte & 0b00000111) << 2)
		| ((byte & 0b00011000) << 3)
		| ((byte & 0b01100000) >> 5)
		| ((byte & 0b10000000) >> 2);
}

void decrypt(char& byte, const unsigned char& key)
{
	byte = ((byte & 0b00011100) >> 2)
		| ((byte & 0b11000000) >> 3)
		| ((byte & 0b00000011) << 5)
		| ((byte & 0b00100000) << 2);

	byte ^= key;
}

void crypt(std::ifstream& in, std::ofstream& out, const Mode& mode, const unsigned char& key)
{
	char byte;
	while (in.read(reinterpret_cast<char*>(&byte), sizeof(unsigned char)))
	{
		(mode == Mode::CRYPT)
			? encrypt(byte, key)
			: decrypt(byte, key);
		out.write(reinterpret_cast<char*>(&byte), sizeof(unsigned char));
	}
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = parseArgs(argc, argv);

		std::ifstream input;
		input.open(args.input);
		if (!input.is_open())
		{
			throw std::ios_base::failure(buildFileReadingError());
		}

		std::ofstream output;
		output.open(args.output);
		if (!output.is_open())
		{
			throw std::ios_base::failure(buildFileWritingError());
		}

		crypt(input, output, args.mode, args.key);

		if (input.bad())
		{
			throw std::ios_base::failure(buildFileReadingError());
		}

		if (!output.flush())
		{
			throw std::ios_base::failure(buildFileWritingError());
		}
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	catch (const std::out_of_range& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	catch (const std::ios_base::failure& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
