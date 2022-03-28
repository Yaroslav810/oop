#include "CCarController.h"

CController::CController(CCar& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
{
}

CController::~CController()
{
}

void CController::Start()
{
	std::string str;
	try
	{
		bool isExit = false;
		while (std::getline(m_input, str) && !isExit)
		{
			auto command = ParseCommand(str);
			ExecuteCommand(command);

			if (command.type == CommandType::EXIT)
			{
				isExit = true;
			}
		}
	}
	catch (const std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
}

Command CController::ParseCommand(const std::string& str)
{
	std::stringstream line(str);

	std::string type;
	int args = 0;

	line >> type;
	auto commandType = ParseCommandType(type);
	if (commandType == CommandType::SET_SPEED || commandType == CommandType::SET_GEAR)
	{
		line >> args;
	}

	return {
		.type = commandType,
		.args = args,
	};
}

CommandType CController::ParseCommandType(const std::string& str)
{
	if (str == "Info")
	{
		return CommandType::INFO;
	}
	else if (str == "EngineOn")
	{
		return CommandType::ENGINE_ON;
	}
	else if (str == "EngineOff")
	{
		return CommandType::ENGINE_OFF;
	}
	else if (str == "SetGear")
	{
		return CommandType::SET_GEAR;
	}
	else if (str == "SetSpeed")
	{
		return CommandType::SET_SPEED;
	}
	else if (str == "Help")
	{
		return CommandType::HELP;
	}
	else if (str == "Exit")
	{
		return CommandType::EXIT;
	}

	throw std::invalid_argument("Unknown command: " + str + ".");
}

void CController::ExecuteCommand(const Command& command)
{
	switch (command.type)
	{
	case CommandType::INFO:
		ExecuteInfoCommand();
		break;
	case CommandType::ENGINE_ON:
		ExecuteEngineOnCommand();
		break;
	case CommandType::ENGINE_OFF:
		ExecuteEngineOffCommand();
		break;
	case CommandType::SET_GEAR:
		ExecuteSetGearCommand(command.args);
		break;
	case CommandType::SET_SPEED:
		ExecuteSetSpeedCommand(command.args);
		break;
	case CommandType::HELP:
		ExecuteHelpCommand();
	case CommandType::EXIT:
		break;
	}
}

void CController::ExecuteInfoCommand()
{
	auto direction = "";
	switch (m_car.GetDirection())
	{
	case Direction::FORWARD:
		direction = "forward";
		break;
	case Direction::BACK:
		direction = "back";
		break;
	case Direction::NO_MOVEMENT:
		direction = "no movement";
	}
	m_output << "State engine: " << (m_car.IsTurnedOn() ? "On" : "Off") << std::endl;
	m_output << "Direction movement: " << direction << std::endl;
	m_output << "Current speed: " << m_car.GetSpeed() << std::endl;
	m_output << "Current gear: " << m_car.GetGear() << std::endl;
}

void CController::ExecuteEngineOnCommand()
{
	if (m_car.TurnOnEngine())
	{
		m_output << "The engine is successfully switched on" << std::endl;
	}
	else
	{
		m_output << "Failed to turn on the engine" << std::endl;
	}
}

void CController::ExecuteEngineOffCommand()
{
	if (m_car.TurnOffEngine())
	{
		m_output << "The engine is successfully switched off" << std::endl;
	}
	else
	{
		m_output << "Failed to turn off the engine" << std::endl;
	}
}

void CController::ExecuteSetGearCommand(int value)
{
	if (m_car.SetGear(value))
	{
		m_output << "The gear is set to " + std::to_string(value) << std::endl;
	}
	else
	{
		m_output << "It is not possible to set the gear to " + std::to_string(value) << std::endl;
	}
}

void CController::ExecuteSetSpeedCommand(int value)
{
	if (m_car.SetSpeed(value))
	{
		m_output << "The speed is set to " + std::to_string(value) << std::endl;
	}
	else
	{
		m_output << "It is not possible to set the speed to " + std::to_string(value) << std::endl;
	}
}

void CController::ExecuteHelpCommand()
{
	m_output << "The following commands are available: " << std::endl;
	m_output << "> Help - show available commands" << std::endl;
	m_output << "> Info - information about the state a car" << std::endl;
	m_output << "> EngineOn - turning on the engines" << std::endl;
	m_output << "> EngineOff - turning off the engines" << std::endl;
	m_output << "> SetGear <-1, 0, 1, 2, 3, 4, 5> - setting up the gear" << std::endl;
	m_output << "> SetSpeed <int> - setting the speed" << std::endl;
	m_output << "> Exit - exiting the program" << std::endl;
}
