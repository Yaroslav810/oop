#pragma once
#include <iostream>
#include <map>

using MapDecodeHTML = std::map<std::string, char>;

std::string HtmlDecode(std::string const& html);

void CopyStreamWithDecode(std::istream& in, std::ostream& out);
