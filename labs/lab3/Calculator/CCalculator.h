#pragma once
#include "stdafx.h"

constexpr auto INVALID_IDENTIFIER = "Invalid identifier";
constexpr auto REDEFINITION = "Re-declaring the identifier";
constexpr auto UNDECLARED = "Using an undeclared identifier";
constexpr auto INVALID_EXPRESSION = "Invalid function expression";

class CCalculator
{
public:
	enum class Operation
	{
		ADDITION,
		SUBTRACTION,
		MULTIPLICATION,
		DIVISION,
		NONE,
	};
	using Identifier = std::string;
	using Value = double;
	using Expression = struct
	{
		Identifier firstOperandId;
		Identifier secondOperandId;
		Operation operation;
	};
	using Values = std::map<Identifier, Value>;
	using Vars = std::map<Identifier, Value>;
	using Functions = std::map<Identifier, Expression>;

	CCalculator();

	void CreateVar(const Identifier& identifier);
	void AssignmentLet(const Identifier& identifier, Value value);
	void AssignmentLet(const Identifier& identifier1, const Identifier& identifier2);
	void CreateFunction(const Identifier& identifier1, const Identifier& identifier2);
	void CreateFunction(const Identifier& identifier, const Expression& expression);

	Value GetIdentifierValue(const Identifier& identifier) const;
	Values GetVars() const;
	Values GetFunctions() const;

private:
	static constexpr auto NAN_VAL = std::numeric_limits<Value>::quiet_NaN();

	bool IsValidIdentifier(const Identifier& identifier) const;
	bool IsIdentifierDefined(const Identifier& identifier) const;
	Value CalculateFunction(const Expression& expression) const;

	Vars m_vars;
	Functions m_functions;
};
