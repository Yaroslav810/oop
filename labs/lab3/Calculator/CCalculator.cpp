#include "CCalculator.h"

CCalculator::CCalculator()
	: m_vars({})
	, m_functions({})
{
}

void CCalculator::CreateVar(const Identifier& identifier)
{
	if (!IsValidIdentifier(identifier))
	{
		throw std::invalid_argument(INVALID_IDENTIFIER);
	}

	if (IsIdentifierDefined(identifier))
	{
		throw std::runtime_error(REDEFINITION);
	}

	m_vars[identifier] = NAN_VAL;
}

void CCalculator::AssignmentLet(const Identifier& identifier, Value value)
{
}

void CCalculator::AssignmentLet(const Identifier& identifier1, const Identifier& identifier2)
{
}

void CCalculator::CreateFunction(const Identifier& identifier1, const Identifier& identifier2)
{
}

void CCalculator::CreateFunction(const Identifier& identifier, const Expression& expression)
{
}

CCalculator::Value CCalculator::GetIdentifierValue(const Identifier& identifier) const
{
	return NAN_VAL;
}

CCalculator::Vars CCalculator::GetVars() const
{
	return {};
}

CCalculator::Functions CCalculator::GetFunctions() const
{
	return {};
}

bool CCalculator::IsValidIdentifier(const Identifier& identifier) const
{
	if (identifier.empty() || std::isdigit(identifier[0]))
	{
		return false;
	}

	std::regex regex("\\w+");
	return std::regex_match(identifier, regex);
}

bool CCalculator::IsIdentifierDefined(const Identifier& identifier) const
{
	if (m_vars.find(identifier) != m_vars.end())
	{
		return true;
	}

	return m_functions.find(identifier) != m_functions.end();
}
