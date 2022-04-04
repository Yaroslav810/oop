#include "./decode.h"

using MapDecodeHTML = std::map<std::string, char>;

MapDecodeHTML InitMapDecode()
{
	return {
		{ "&quot;", '"' },
		{ "&apos;", '\'' },
		{ "&lt;", '<' },
		{ "&gt;", '>' },
		{ "&amp;", '&' },
	};
}

std::string DecodeHTMLEntity(const std::string& subject, const MapDecodeHTML& map, size_t& foundPos)
{
	// subject обрезать
	// map find
	std::string res;
	for (const auto& [search, replacement] : map)
	{
		if (std::string(subject, foundPos, search.size()) == search)
		{
			foundPos += search.size();
			return std::string(1, replacement);
		}
	}

	foundPos++;
	return std::string(1, subject[foundPos - 1]);
}

std::string HtmlDecode(std::string const& html, MapDecodeHTML const& map)
{
	size_t pos = 0;
	std::string result;
	while (pos < html.length())
	{
		size_t foundPos = html.find('&', pos);
		result.append(html, pos, foundPos - pos);
		if (foundPos == std::string::npos)
		{
			break;
		}

		result.append(DecodeHTMLEntity(html, map, foundPos));
		pos = foundPos;
	}

	return result;
}

void CopyStreamWithDecode(std::istream& in, std::ostream& out)
{
	auto map = InitMapDecode();

	std::string line;
	while (std::getline(in, line))
	{
		out << HtmlDecode(line, map) << std::endl;
	}
}
