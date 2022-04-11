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
	if (!IsIdentifierDefined(identifier))
	{
		CreateVar(identifier);
	}

	m_vars[identifier] = value;
}

void CCalculator::AssignmentLet(const Identifier& identifier1, const Identifier& identifier2)
{
	if (!IsIdentifierDefined(identifier2))
	{
		throw std::runtime_error(UNDECLARED);
	}

	AssignmentLet(identifier1, GetIdentifierValue(identifier2));
}

void CCalculator::CreateFunction(const Identifier& identifier1, const Identifier& identifier2)
{
	if (!IsValidIdentifier(identifier1))
	{
		throw std::invalid_argument(INVALID_IDENTIFIER);
	}
	if (IsIdentifierDefined(identifier1))
	{
		throw std::runtime_error(REDEFINITION);
	}

	if (!IsIdentifierDefined(identifier2))
	{
		throw std::runtime_error(UNDECLARED);
	}

	m_functions[identifier1] = {
		.firstOperandId = identifier2,
		.secondOperandId = "",
		.operation = Operation::NONE,
	};
}

void CCalculator::CreateFunction(const Identifier& identifier, const Expression& expression)
{
	if (!IsValidIdentifier(identifier))
	{
		throw std::invalid_argument(INVALID_IDENTIFIER);
	}
	if (IsIdentifierDefined(identifier))
	{
		throw std::runtime_error(REDEFINITION);
	}
	if (!IsIdentifierDefined(expression.firstOperandId)
		|| !IsIdentifierDefined(expression.secondOperandId)
		|| expression.operation == Operation::NONE)
	{
		throw std::runtime_error(UNDECLARED);
	}

	m_functions[identifier] = expression;
}

CCalculator::Value CCalculator::GetIdentifierValue(const Identifier& identifier) const
{
	if (auto it = m_vars.find(identifier);
		it != m_vars.end())
	{
		return it->second;
	}

	if (auto it = m_functions.find(identifier);
		it != m_functions.end())
	{
		return CalculateFunction(it->second);
	}

	throw std::runtime_error(UNDECLARED);
}

CCalculator::Vars CCalculator::GetVars() const
{
	return m_vars;
}

CCalculator::Functions CCalculator::GetFunctions() const
{
	return m_functions;
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

CCalculator::Value CCalculator::CalculateFunction(const Expression& expression) const
{
	auto firstValue = GetIdentifierValue(expression.firstOperandId);
	switch (expression.operation)
	{
	case Operation::ADDITION:
		return firstValue + GetIdentifierValue(expression.firstOperandId);
	case Operation::SUBTRACTION:
		return firstValue - GetIdentifierValue(expression.firstOperandId);
	case Operation::MULTIPLICATION:
		return firstValue * GetIdentifierValue(expression.firstOperandId);
	case Operation::DIVISION:
		return firstValue / GetIdentifierValue(expression.firstOperandId);
	case Operation::NONE:
		return firstValue;
	}

	throw std::runtime_error(INVALID_EXPRESSION);
}
