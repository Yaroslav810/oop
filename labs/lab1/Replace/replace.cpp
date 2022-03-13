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

std::string BuildInvalidArgcError()
{
	return "Invalid argument count!"
		   "\n"
		   "Usage: replace.exe <inputFile> <outputFile> <searchString> <replaceString>"
		   "\n";
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

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::invalid_argument(BuildInvalidArgcError());
	}

	return {
		.inputFile = argv[1],
		.outputFile = argv[2],
		.searchString = argv[3],
		.replaceString = argv[4]
	};
}

std::string ReplaceString(const std::string& subject,
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

void CopyFileWithReplace(std::istream& input,
	std::ostream& output,
	const std::string& searchString,
	const std::string& replacementString)
{
	std::string line;
	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << std::endl;
	}
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);

		std::ifstream inputFile;
		inputFile.open(args.inputFile);
		if (!inputFile.is_open())
		{
			throw std::ios_base::failure(BuildFileReadingError());
		}

		std::ofstream outputFile;
		outputFile.open(args.outputFile);
		if (!outputFile.is_open())
		{
			throw std::ios_base::failure(BuildFileWritingError());
		}

		CopyFileWithReplace(inputFile, outputFile, args.searchString, args.replaceString);

		if (inputFile.bad())
		{
			throw std::ios_base::failure(BuildFileReadingError());
		}

		if (!outputFile.flush())
		{
			throw std::ios_base::failure(BuildFileWritingError());
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
