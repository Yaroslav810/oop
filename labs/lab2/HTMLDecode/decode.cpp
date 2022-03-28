#include "./decode.h"

MapDecodeHTML InitMapDecode()
{
	MapDecodeHTML mapDecode = {
		{"&quot;", '"'},
		{"&apos;", '\''},
		{"&lt;", '<'},
		{"&gt;", '>'},
		{"&amp;", '&'},
	};
	return mapDecode;
}

void DecodeHTMLEntity(std::string const& subject, MapDecodeHTML const& map, size_t foundPos)
{
	//
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

		result.append(replacementString);
		pos = foundPos + searchString.length();
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
