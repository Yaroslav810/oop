#include "stdafx.h"
#include "CCalculator.h"

class CCalculatorController
{
public:
	CCalculatorController(CCalculator& car, std::istream& input, std::ostream& output);
	void Start();

private:
	static constexpr int OUTPUT_ACCURACY = 2;

	enum class CommandType {
		CREATE_VAR,
		ASSIGN_VAR,
		CREATE_FUNCTION,
		PRINT,
		PRINT_VARS,
		PRINT_FUNCTIONS,
		EXIT,
		HELP,
	};
	struct Command {
		CommandType type;
		std::string arguments;
	};
	struct AssignVarType {
		CCalculator::Identifier identifier;
		std::variant<CCalculator::Value, CCalculator::Identifier> value;
	};
	struct CreateFunctionType {
		CCalculator::Identifier identifier;
		std::variant<CCalculator::Identifier, CCalculator::Expression> value;
	};

	Command ParseCommand(const std::string& str);
	std::optional<CommandType> ParseCommandType(const std::string str);
	void ExecuteCommand(const Command& command);
	void ExecuteHelpCommand();
	void ExecuteCreateVarCommand(const std::string& str);
	void ExecuteAssignVarCommand(const std::string& str);
	void ExecuteCreateFunction(const std::string& str);
	void ExecutePrintCommand(const std::string& str);
	void ExecutePrintVarsCommand();
	void ExecutePrintFnsCommand();

	CCalculator::Identifier ParseIdentifier(const std::string& str);
	AssignVarType ParseAssign(const std::string& str);
	CreateFunctionType ParseFunction(const std::string& str);
	void PrintValues(const CCalculator::Values& values);

	CCalculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;
};
