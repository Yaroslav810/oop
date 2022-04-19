#include "CCalculatorController.h"

CCalculatorController::CCalculatorController(CCalculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
{
	m_output << std::fixed << std::setprecision(OUTPUT_ACCURACY);
}

void CCalculatorController::Start()
{
	std::string str;
	bool isExit = false;
	while (!isExit && m_output << "> " && std::getline(m_input, str))
	{
		try
		{
			auto command = ParseCommand(str);
			ExecuteCommand(command);
			command.type == CommandType::EXIT && (isExit = true);
		}
		catch (const std::exception& e)
		{
			m_output << e.what() << std::endl;
			m_output << std::endl;
		}
	}
}

CCalculatorController::Command CCalculatorController::ParseCommand(const std::string& str)
{
	std::stringstream line(str);

	std::string type;
	std::string arguments;

	line >> type;
	auto commandType = ParseCommandType(type);
	if (!commandType.has_value())
	{
		throw std::invalid_argument("Unknown command!");
	}
	line >> std::ws;
	std::getline(line, arguments);

	return {
		.type = commandType.value(),
		.arguments = arguments,
	};
}

std::optional<CCalculatorController::CommandType> CCalculatorController::ParseCommandType(const std::string str)
{
	if (str == "var")
	{
		return CommandType::CREATE_VAR;
	}
	else if (str == "let")
	{
		return CommandType::ASSIGN_VAR;
	}
	else if (str == "fn")
	{
		return CommandType::CREATE_FUNCTION;
	}
	else if (str == "print")
	{
		return CommandType::PRINT;
	}
	else if (str == "printvars")
	{
		return CommandType::PRINT_VARS;
	}
	else if (str == "printfns")
	{
		return CommandType::PRINT_FUNCTIONS;
	}
	else if (str == "help")
	{
		return CommandType::HELP;
	}
	else if (str == "exit")
	{
		return CommandType::EXIT;
	}

	return std::nullopt;
}

void CCalculatorController::ExecuteCommand(const Command& command)
{
	switch (command.type)
	{
	case CommandType::CREATE_VAR:
		ExecuteCreateVarCommand(command.arguments);
		break;
	case CommandType::ASSIGN_VAR:
		ExecuteAssignVarCommand(command.arguments);
		break;
	case CommandType::CREATE_FUNCTION:
		ExecuteCreateFunction(command.arguments);
		break;
	case CommandType::PRINT:
		ExecutePrintCommand(command.arguments);
		break;
	case CommandType::PRINT_VARS:
		ExecutePrintVarsCommand();
		break;
	case CommandType::PRINT_FUNCTIONS:
		ExecutePrintFnsCommand();
		break;
	case CommandType::HELP:
		ExecuteHelpCommand();
	case CommandType::EXIT:
		break;
	default:
		throw std::invalid_argument("Undefined state when executing a command");
	}
}

void CCalculatorController::ExecuteHelpCommand()
{
	auto indent = std::string(5, ' ');
	m_output << "The following commands are available: " << std::endl;
	m_output << indent << "- var <identifier> - creating a variable" << std::endl;
	m_output << indent << "- let <identifier> = <number> - assigning a numeric value to a variable" << std::endl;
	m_output << indent << "- let <identifier1> = <identifier2> - assigning a variable value to another variable" << std::endl;
	m_output << indent << "- fn <identifier1> = <identifier2> - creating a function with a variable value" << std::endl;
	m_output << indent << "- fn <identifier1> = <identifier2> <operator> <identifier3> - creating an expression" << std::endl;
	m_output << indent << "- print <identifier> - creating an expression - print the value of a variable or function" << std::endl;
	m_output << indent << "- printvars - output all variables" << std::endl;
	m_output << indent << "- printfns - output all functions" << std::endl;
	m_output << indent << "- exit - exiting the program" << std::endl;
	m_output << std::endl;
}

void CCalculatorController::ExecuteCreateVarCommand(const std::string& str)
{
	m_calculator.CreateVar(ParseIdentifier(str));
}

void CCalculatorController::ExecuteAssignVarCommand(const std::string& str)
{
	auto data = ParseAssign(str);
	if (std::holds_alternative<CCalculator::Value>(data.value)) {
		m_calculator.AssignmentLet(data.identifier, std::get<CCalculator::Value>(data.value));
	}
	if (std::holds_alternative<CCalculator::Identifier>(data.value)) {
		m_calculator.AssignmentLet(data.identifier, std::get<CCalculator::Identifier>(data.value));
	}

	// TODO: Выбросить и проверить исключение
	throw std::invalid_argument("");
}

void CCalculatorController::ExecuteCreateFunction(const std::string& str)
{
	// TODO: Написать функцию
}

void CCalculatorController::ExecutePrintCommand(const std::string& str)
{
	m_output << m_calculator.GetIdentifierValue(ParseIdentifier(str)) << std::endl;
}

void CCalculatorController::ExecutePrintVarsCommand()
{
	PrintValues(m_calculator.GetVars());
}

void CCalculatorController::ExecutePrintFnsCommand()
{
	PrintValues(m_calculator.GetFunctions());
}

CCalculator::Identifier CCalculatorController::ParseIdentifier(const std::string& str)
{
	std::stringstream ss(str);

	CCalculator::Identifier identifier;
	ss >> identifier;

	return identifier;
}

CCalculatorController::AssignVarType CCalculatorController::ParseAssign(const std::string& str)
{
	std::stringstream line(str);
	CCalculator::Identifier identifier;
	if (!std::getline(line, identifier, '=')) {
		// Todo: Выбросить и проаверить исключение
		throw std::invalid_argument("");
	}
	std::string value;
	line >> value;
	if (value.empty()) {
		// Todo: Выбросить и проаверить исключение
		throw std::invalid_argument("");
	}
	const auto idEnd = identifier.find_last_not_of(' ');
	identifier.substr(0, idEnd + 1);
	try
	{
		return {
			.identifier = identifier,
			.value = std::stoi(value),
		};
	}
	catch (const std::invalid_argument& e)
	{
		return {
			.identifier = identifier,
			.value = value,
		};
	}
}

CCalculatorController::CreateFunctionType CCalculatorController::ParseFunction(const std::string& str)
{
	// TODO: Написать функцию

	return {};
}

void CCalculatorController::PrintValues(const CCalculator::Values& values)
{
	for (const auto& [identifier, value] : values)
	{
		m_output << identifier << ": " << value << std::endl;
	}
	m_output << std::endl;
}
