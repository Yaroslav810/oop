#pragma once
#include <iostream>

class CUrlParsingError : public std::invalid_argument
{
public:
	explicit CUrlParsingError(const std::string& msg);
};
