#include "dictionary.h"
#include <algorithm>

std::string GetLowercaseString(const std::string& str)
{
	auto newWord = str;
	std::transform(newWord.begin(), newWord.end(), newWord.begin(), tolower);
	return newWord;
}

void PrintDictionary(std::ostream& output, const Dictionary& dictionary)
{
	for (const auto& [word, translations] : dictionary)
	{
		output << word << ": ";
		for (const auto& translate : translations)
		{
			output << translate << ' ';
		}
		output << std::endl;
	}
}

void AddTranslation(Dictionary& dictionary, const std::string& word, const std::string& translation)
{
	dictionary[GetLowercaseString(word)].insert(translation);
}

Translations GetTranslate(const Dictionary& dictionary, const std::string& word)
{
	auto it = dictionary.find(GetLowercaseString(word));
	if (it == dictionary.end())
	{
		return {};
	}

	return it->second;
}

bool HaveWordInDictionary(const Dictionary& dictionary, const std::string& word)
{
	auto it = dictionary.find(GetLowercaseString(word));
	return it != dictionary.end();
}
