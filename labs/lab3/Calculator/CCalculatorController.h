#pragma once
#include "stdafx.h"
#include "CCalculator.h"

class CCalculatorController
{
public:
	CCalculatorController(CCalculator& car, std::istream& input, std::ostream& output);
	void Start();

private:
	static constexpr int OUTPUT_ACCURACY = 2;

	enum class CommandType
	{
		CREATE_VAR,
		ASSIGN_VAR,
		CREATE_FUNCTION,
		PRINT,
		PRINT_VARS,
		PRINT_FUNCTIONS,
		EXIT,
		HELP,
	};
	struct Command
	{
		CommandType type;
		std::string arguments;
	};
	struct AssignVarType
	{
		CCalculator::Identifier identifier;
		std::variant<CCalculator::Value, CCalculator::Identifier> value;
	};
	struct CreateFunctionType
	{
		CCalculator::Identifier identifier;
		std::variant<CCalculator::Identifier, CCalculator::Expression> value;
	};

	static Command ParseCommand(const std::string& str);
	static std::optional<CommandType> ParseCommandType(const std::string& str);
	void ExecuteCommand(const Command& command);
	void ExecuteHelpCommand();
	void ExecuteCreateVarCommand(const std::string& str);
	void ExecuteAssignVarCommand(const std::string& str);
	void ExecuteCreateFunction(const std::string& str);
	void ExecutePrintCommand(const std::string& str);
	void ExecutePrintVarsCommand();
	void ExecutePrintFnsCommand();

	static CCalculator::Identifier ParseIdentifier(const std::string& str);
	static CCalculator::Identifier ParseIdentifier(std::stringstream& ss);
	static AssignVarType ParseAssign(const std::string& str);
	static std::string ParseAssignArguments(std::stringstream& ss);
	static CreateFunctionType ParseFunction(const std::string& str);
	static std::optional<CCalculator::Operation> ParseOperation(std::stringstream& ss);
	void PrintValues(const CCalculator::Values& values);

	CCalculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;
};
