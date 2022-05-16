#pragma once
#include "dictionary.h"
#include <fstream>

constexpr auto COMPLETION_PROGRAM = "...";
constexpr auto ENTRY = "> ";

void Start(std::istream& input, std::ostream& output, const std::string& dictionaryPath);
