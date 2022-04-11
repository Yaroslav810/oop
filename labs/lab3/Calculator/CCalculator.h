#pragma once
#include "stdafx.h"

constexpr auto INVALID_IDENTIFIER = "Invalid identifier";
constexpr auto REDEFINITION = "Re-declaring the identifier";

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
	using Vars = std::map<Identifier, Value>;
	using Functions = std::map<Identifier, Expression>;

	CCalculator();

	void CreateVar(const Identifier& identifier);
	void AssignmentLet(const Identifier& identifier, Value value);
	void AssignmentLet(const Identifier& identifier1, const Identifier& identifier2);
	void CreateFunction(const Identifier& identifier1, const Identifier& identifier2);
	void CreateFunction(const Identifier& identifier, const Expression& expression);

	Value GetIdentifierValue(const Identifier& identifier) const;
	Vars GetVars() const;
	Functions GetFunctions() const;

private:
	static constexpr auto NAN_VAL = std::numeric_limits<Value>::quiet_NaN();

	bool IsValidIdentifier(const Identifier& identifier) const;
	bool IsIdentifierDefined(const Identifier& identifier) const;

	Vars m_vars;
	Functions m_functions;
};
