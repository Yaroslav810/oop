#pragma once
#include <iostream>
#include <map>
#include <set>

using Translations = std::set<std::string>;
using Dictionary = std::map<std::string, Translations>;

void PrintDictionary(std::ostream& output, const Dictionary& dictionary);
void AddTranslation(Dictionary& dictionary, const std::string& word, const std::string& translation);
Translations GetTranslate(const Dictionary& dictionary, const std::string& word);
bool HaveWordInDictionary(const Dictionary& dictionary, const std::string& word);
