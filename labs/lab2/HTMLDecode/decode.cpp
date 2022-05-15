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

char DecodeHTMLEntity(const std::string& subject, const MapDecodeHTML& map, size_t& foundPos)
{
	// TODO: subject обрезать
	// TODO: map find
	auto it = map.find(subject);
	if (it != map.end()) {
		foundPos += it->first.size();
		return it->second;
	}

	foundPos++;
	return subject[foundPos - 1];
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

		size_t foundEndEntity = html.find(';', foundPos);
		if (foundEndEntity == std::string::npos)
		{
			result.append(html, foundPos, foundEndEntity - foundPos);
			break;
		}
		result += DecodeHTMLEntity(html.substr(foundPos, foundEndEntity - foundPos + 1), map, foundPos);
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
