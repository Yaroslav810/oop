#pragma once
#include "CUrlParsingError.h"
#include <regex>

class CHttpUrl
{
public:
	enum class Protocol
	{
		HTTP,
		HTTPS,
	};
	using Port = unsigned short;

	explicit CHttpUrl(std::string const& url);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = CHttpUrl::Protocol::HTTP);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		CHttpUrl::Port port);

	[[nodiscard]] std::string GetURL() const;
	[[nodiscard]] std::string GetDomain() const;
	[[nodiscard]] std::string GetDocument() const;
	[[nodiscard]] Protocol GetProtocol() const;
	[[nodiscard]] Port GetPort() const;

	[[nodiscard]] static std::string GetStringFromProtocol(Protocol const& protocol);

private:
	static constexpr Port MIN_PORT = 1;
	static constexpr Port MAX_PORT = 65535;

	static constexpr Port DEFAULT_HTTP_PORT = 80;
	static constexpr Port DEFAULT_HTTPS_PORT = 443;

	static Port GetDefaultPort(Protocol const& protocol);
	static std::string GetStringInLowerCase(std::string const& string);

	static Protocol ParseProtocol(std::string const& protocol);
	static std::string ParseDomain(std::string const& domain);
	static Port ParsePort(std::string const& port, CHttpUrl::Protocol const& protocol);
	static std::string ParseDocument(std::string const& document);

	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	Port m_port;
};
