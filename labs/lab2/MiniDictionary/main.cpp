#include "dictionaryController.h"
#include <Windows.h>
#include <clocale>

constexpr auto BuildInvalidArgcError = "Invalid argument count"
									   "\n"
									   "Usage: dictionary.exe <dictionaryPath>";

std::string ParseDictionaryPath(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument(BuildInvalidArgcError);
	}

	return argv[1];
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(866);
	SetConsoleOutputCP(866);

	try
	{
		auto dictionaryPath = ParseDictionaryPath(argc, argv);
		Start(std::cin, std::cout, dictionaryPath);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
