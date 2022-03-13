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

std::string GetString(int n)
{
	return std::to_string(n);
}

std::string BuildInvalidArgcError()
{
	return "Invalid argument count"
		   "\n"
		   "Usage:"
		   "\n"
		   "     - crypt.exe crypt <inputFile> <outputFile> <key> for crypt"
		   "\n"
		   "     - crypt.exe decrypt <inputFile> <outputFile> <key> for decrypt";
}

std::string BuildInvalidModeError(const std::string& str)
{
	return "Failed to recognize the mode!"
		   "\n"
		   "Expected <"
		+ CRYPT_MODE + "> or <" + DECRYPT_MODE + ">, but received: " + str + "\n";
}

std::string BuildInvalidKeyError(const std::string& str)
{
	return "Invalid key!"
		   "\n"
		   "Use a number from "
		+ GetString(MIN_KEY) + " to " + GetString(MAX_KEY) + "\n";
}

std::string BuildFileReadingError()
{
	return "Error reading the file!"
		   "\n"
		   "It is possible that the file is corrupted or there are no permissions to read it"
		   "\n";
}

std::string BuildFileWritingError()
{
	return "Error writing the file!"
		   "\n"
		   "It is possible that the file is corrupted or there are no permissions to write it"
		   "\n";
}

std::string BuildInvalidNumberSystemError()
{
	return "To indicate the key, use the decimal system of reading!"
		   "\n";
}

Mode ParseMode(const std::string& mode)
{
	if (mode == CRYPT_MODE)
	{
		return Mode::CRYPT;
	}
	if (mode == DECRYPT_MODE)
	{
		return Mode::DECRYPT;
	}

	throw std::invalid_argument(BuildInvalidModeError(mode));
}

int CharToDigit(char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return ch - '0';
	}

	throw std::invalid_argument(BuildInvalidNumberSystemError());
}

int ConcatenateDigitToNumber(int number, int digit, bool isNegative)
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

int StringToInt(const std::string& str)
{
	if (str.empty())
	{
		throw std::invalid_argument("Missing number");
	}

	int number = 0;
	bool isNegativeNumber = str[0] == '-';

	for (int i = isNegativeNumber ? 1 : 0; i < str.length(); ++i)
	{
		auto digit = CharToDigit(str[i]);

		number = ConcatenateDigitToNumber(number, digit, isNegativeNumber);
	}

	return number;
}

unsigned char ParseKey(const std::string& key)
{
	auto number = StringToInt(key);
	if (number < MIN_KEY || number > MAX_KEY)
	{
		throw std::invalid_argument(BuildInvalidKeyError(key));
	}

	return static_cast<unsigned char>(number);
}

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::invalid_argument(BuildInvalidArgcError());
	}

	return {
		.mode = ParseMode(argv[1]),
		.input = argv[2],
		.output = argv[3],
		.key = ParseKey(argv[4]),
	};
}

void Encrypt(unsigned char& byte, unsigned char key)
{
	byte ^= key;

	byte = ((byte & 0b00000111) << 2)
		| ((byte & 0b00011000) << 3)
		| ((byte & 0b01100000) >> 5)
		| ((byte & 0b10000000) >> 2);
}

void Decrypt(unsigned char& byte, unsigned char key)
{
	byte = ((byte & 0b00011100) >> 2)
		| ((byte & 0b11000000) >> 3)
		| ((byte & 0b00000011) << 5)
		| ((byte & 0b00100000) << 2);

	byte ^= key;
}

// Разделить на Encrypt и decript, istream, reinterpret_cast: char напрямую пихать в Encrypt и Decrypt
void Crypt(std::ifstream& in, std::ofstream& out, Mode mode, unsigned char key)
{
	unsigned char byte;
	while (in.read(reinterpret_cast<char*>(&byte), sizeof(unsigned char)))
	{
		(mode == Mode::CRYPT)
			? Encrypt(byte, key)
			: Decrypt(byte, key);
		out.write(reinterpret_cast<char*>(&byte), sizeof(unsigned char));
	}
}

void CheckOpeningFilesError(std::ifstream& input, std::ofstream& output)
{
	if (!input.is_open())
	{
		throw std::ios_base::failure(BuildFileReadingError());
	}
	if (!output.is_open())
	{
		throw std::ios_base::failure(BuildFileWritingError());
	}
}

void CheckFileReadingError(std::ifstream& input)
{
	if (input.bad())
	{
		throw std::ios_base::failure(BuildFileReadingError());
	}
}

void CheckFileWritingError(std::ofstream& output)
{
	if (!output.flush())
	{
		throw std::ios_base::failure(BuildFileWritingError());
	}
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);

		// Общая функция
		std::ifstream input;
		input.open(args.input);
		std::ofstream output;
		output.open(args.output);

		CheckOpeningFilesError(input, output);

		Crypt(input, output, args.mode, args.key);

		CheckFileReadingError(input);
		CheckFileWritingError(output);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
