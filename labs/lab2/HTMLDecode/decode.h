#pragma once
#include <iostream>
#include <map>

using MapDecodeHTML = std::map<std::string, char>;

MapDecodeHTML InitMapDecode();

std::string DecodeHTMLEntity(std::string const& subject, MapDecodeHTML const& map, size_t& foundPos);

std::string HtmlDecode(std::string const& html);

void CopyStreamWithDecode(std::istream& in, std::ostream& out);
