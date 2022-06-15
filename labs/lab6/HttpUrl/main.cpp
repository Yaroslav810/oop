#include "CHttpUrl.h"

void PrintUrlInfoToStream(std::ostream& output, CHttpUrl const& httpUrl)
{
	output << "Url: " << httpUrl.GetURL() << std::endl;
	output << "Protocol: " << CHttpUrl::GetStringFromProtocol(httpUrl.GetProtocol()) << std::endl;
	output << "Domain: " << httpUrl.GetDomain() << std::endl;
	output << "Port: " << httpUrl.GetPort() << std::endl;
	output << "Document: " << httpUrl.GetDocument() << std::endl;
}

int main()
{
	std::string line;
	while (std::cout << "> " && std::getline(std::cin, line))
	{
		try
		{
			CHttpUrl url(line);
			PrintUrlInfoToStream(std::cout, url);
		}
		catch (CUrlParsingError const& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	return 0;
}
