// Replace.cpp : Defines the entry point for the console application.

#include <fstream>
#include <iostream>
#include <string>

struct Args
{
	std::string inputFile;
	std::string outputFile;
	std::string searchString;
	std::string replaceString;
};

std::string buildInvalidArgcError()
{
	return "Invalid argument count!"
		   "\n"
		   "Usage: replace.exe <inputFile> <outputFile> <searchString> <replaceString>"
		   "\n";
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

Args parseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::invalid_argument(buildInvalidArgcError());
	}

	return {
		.inputFile = argv[1],
		.outputFile = argv[2],
		.searchString = argv[3],
		.replaceString = argv[4]
	};
}

std::string replaceString(const std::string& subject,
	const std::string& searchString,
	const std::string& replacementString)
{
	size_t pos = 0;
	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);
		if (foundPos == std::string::npos)
		{
			break;
		}

		result.append(replacementString);
		pos = foundPos + searchString.length();
	}

	return result;
}

void copyFileWithReplace(std::istream& input,
	std::ostream& output,
	const std::string& searchString,
	const std::string& replacementString)
{
	std::string line;
	while (std::getline(input, line))
	{
		output << replaceString(line, searchString, replacementString) << std::endl;
	}
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = parseArgs(argc, argv);

		std::ifstream inputFile;
		inputFile.open(args.inputFile);
		if (!inputFile.is_open()) {
			throw std::ios_base::failure(buildFileReadingError());
		}

		std::ofstream outputFile;
		outputFile.open(args.outputFile);
		if (!outputFile.is_open()) {
			throw std::ios_base::failure(buildFileWritingError());
		}

		copyFileWithReplace(inputFile, outputFile, args.searchString, args.replaceString);

		if (inputFile.bad())
		{
			throw std::ios_base::failure(buildFileReadingError());
		}

		if (!outputFile.flush())
		{
			throw std::ios_base::failure(buildFileWritingError());
		}
	}
	catch (const std::invalid_argument& e)
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
