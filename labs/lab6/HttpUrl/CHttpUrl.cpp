#include "CHttpUrl.h"

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::smatch result;
	std::regex regular("(https?)"
					   "://"
					   "([0-9a-zA-Z-.]+)"
					   "(?::(\\d+))?"
					   "(/[\\w-\\/.:]*)?",
		std::regex::icase);
	if (!std::regex_match(url, result, regular))
	{
		throw CUrlParsingError("Invalid url");
	}

	m_protocol = ParseProtocol(result[1]);
	m_domain = ParseDomain(result[2]);
	m_port = ParsePort(result[3], m_protocol);
	m_document = ParseDocument(result[4]);
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, CHttpUrl::Protocol protocol)
	: CHttpUrl(domain, document, protocol, GetDefaultPort(protocol))
{
}

CHttpUrl::CHttpUrl(
	const std::string& domain,
	const std::string& document,
	CHttpUrl::Protocol protocol,
	CHttpUrl::Port port)
	: m_protocol(protocol)
	, m_domain(ParseDomain(domain))
	, m_port(port)
	, m_document(ParseDocument(document))
{
}

std::string CHttpUrl::GetURL() const
{
	auto protocol = GetProtocol();
	auto port = GetPort();
	auto result = GetStringFromProtocol(protocol);
	result.append("://");
	result.append(GetDomain());
	result.append((GetDefaultPort(protocol) == port) ? "" : ":" + std::to_string(port));
	result.append(GetDocument());
	return result;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

CHttpUrl::Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

CHttpUrl::Port CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::GetStringFromProtocol(const CHttpUrl::Protocol& protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return "http";
	case Protocol::HTTPS:
		return "https";
	default:
		throw CUrlParsingError("Protocol parsing error");
	}
}

CHttpUrl::Port CHttpUrl::GetDefaultPort(CHttpUrl::Protocol const& protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return DEFAULT_HTTP_PORT;
	case Protocol::HTTPS:
		return DEFAULT_HTTPS_PORT;
	default:
		throw CUrlParsingError("Protocol parsing error");
	}
}

std::string CHttpUrl::GetStringInLowerCase(std::string const& string)
{
	std::string result;
	std::transform(
		string.begin(),
		string.end(),
		std::back_inserter(result),
		[](unsigned char c) {
			return std::tolower(c);
		});

	return result;
}

CHttpUrl::Protocol CHttpUrl::ParseProtocol(std::string const& protocol)
{
	auto protocolInLowerCase = GetStringInLowerCase(protocol);
	if (protocolInLowerCase == "http")
	{
		return CHttpUrl::Protocol::HTTP;
	}
	if (protocolInLowerCase == "https")
	{
		return CHttpUrl::Protocol::HTTPS;
	}
	throw CUrlParsingError("Protocol parsing error");
}

std::string CHttpUrl::ParseDomain(const std::string& domain)
{
	if (domain.empty())
	{
		throw CUrlParsingError("Invalid domain");
	}

	return domain;
}

CHttpUrl::Port CHttpUrl::ParsePort(const std::string& port, CHttpUrl::Protocol const& protocol)
{
	if (port.empty())
	{
		return GetDefaultPort(protocol);
	}

	unsigned long result;
	try
	{
		result = std::stoi(port);
	}
	catch (std::exception const&)
	{
		throw CUrlParsingError("Invalid port");
	}

	if (result < MIN_PORT || result > MAX_PORT)
	{
		auto error = "Invalid port. Acceptable values: " + std::to_string(MIN_PORT) + "..." + std::to_string(MAX_PORT);
		throw CUrlParsingError(error);
	}
	return result;
}

std::string CHttpUrl::ParseDocument(const std::string& document)
{
	if (document.empty())
	{
		return "/";
	}

	if (document[0] != '/')
	{
		return "/" + document;
	}

	return document;
}
