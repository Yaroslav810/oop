#include "dictionaryController.h"
#include <sstream>

void LoadDictionaryFromFile(std::istream& input, Dictionary& dictionary)
{
	std::string line;
	while (std::getline(input, line))
	{
		std::stringstream ss(line);
		std::string word;
		std::getline(ss, word, ':');
		std::string translation;
		while (ss >> translation)
		{
			AddTranslation(dictionary, word, translation);
		}
	}
}

void LoadDictionary(const std::string& dictionaryPath, Dictionary& dictionary)
{
	std::ifstream dictionaryStream(dictionaryPath);
	if (!dictionaryStream.is_open())
	{
		return;
	}

	LoadDictionaryFromFile(dictionaryStream, dictionary);
}

void SaveDictionaryToFile(std::ostream& output, Dictionary& dictionary)
{
	PrintDictionary(output, dictionary);
}

void SaveDictionary(const std::string& dictionaryPath, Dictionary& dictionary)
{
	std::ofstream dictionaryStream(dictionaryPath);
	if (!dictionaryStream.is_open())
	{
		return;
	}

	SaveDictionaryToFile(dictionaryStream, dictionary);
}

bool PrintTranslates(std::ostream& output, const Dictionary& dictionary, const std::string& word)
{
	auto translations = GetTranslate(dictionary, word);
	for (const auto& translate : translations)
	{
		output << translate << ' ';
	}
	output << std::endl;
}

void ProcessEnteredWord(std::istream& input, std::ostream& output, Dictionary& dictionary, const std::string& word, bool& wasChangedInDictionary)
{
	if (HaveWordInDictionary(dictionary, word))
	{
		PrintTranslates(output, dictionary, word);
		return;
	}

	std::string newTranslation;
	output << "Unknown word \"" + word + "\". Enter a translation or an empty line for rejection." << std::endl;
	output << ENTRY;
	std::getline(input, newTranslation);
	std::getline(input, newTranslation);
	if (newTranslation.empty())
	{
		output << "The word \"" + word + "\" is ignored." << std::endl;
		return;
	}
	AddTranslation(dictionary, word, newTranslation);
	wasChangedInDictionary = true;
	output << "The word \"" + word + "\" is saved in the dictionary as \"" + newTranslation + "\"." << std::endl;
}

void ProcessDictionarySaving(std::istream& input, std::ostream& output, Dictionary& dictionary)
{
	output << "Changes have been made to the dictionary. Enter Y or y to save before exiting." << std::endl;

	char ch;
	input >> ch;
	if (std::tolower(ch) == 'y')
	{
		SaveDictionary("dict.txt", dictionary);
	}
	else
	{
		output << "The changes are not saved. Goodbye." << std::endl;
	}
}

void ProcessingInputFromStream(std::istream& input, std::ostream& output, Dictionary& dictionary)
{
	bool wasChangedInDictionary = false;
	std::string word;
	while (true)
	{
		output << ENTRY && input >> word;
		if (word == COMPLETION_PROGRAM)
		{
			break;
		}

		ProcessEnteredWord(input, output, dictionary, word, wasChangedInDictionary);
	}

	if (wasChangedInDictionary)
	{
		ProcessDictionarySaving(input, output, dictionary);
	}
	else
	{
		output << "The changes are not saved. Goodbye." << std::endl;
	}
}

void Start(std::istream& input, std::ostream& output, const std::string& dictionaryPath)
{
	Dictionary dictionary = {};
	LoadDictionary(dictionaryPath, dictionary);
	ProcessingInputFromStream(input, output, dictionary);

	PrintDictionary(output, dictionary);
}
