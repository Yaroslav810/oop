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
			ExecuteUnknownCommand(e.what());
		}
	}
}

CController::Command CController::ParseCommand(const std::string& str)
{
	std::stringstream line(str);

	std::string type;
	int args = 0;

	line >> type;
	auto commandType = ParseCommandType(type);
	if (!commandType.has_value())
	{
		throw std::invalid_argument("Unknown command!");
	}
	if (commandType == CommandType::SET_SPEED || commandType == CommandType::SET_GEAR)
	{
		if (!(line >> args))
		{
			throw std::invalid_argument("Invalid argument!");
		}
	}

	return {
		.type = commandType.value(),
		.args = args,
	};
}

std::optional<CController::CommandType> CController::ParseCommandType(const std::string& str)
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

	return std::nullopt;
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
	default:
		throw std::invalid_argument("Undefined state when executing a command");
	}
}

void CController::ExecuteInfoCommand()
{
	m_output << "State engine: " << (m_car.IsTurnedOn() ? "On" : "Off") << std::endl;
	m_output << "Direction movement: " << DirectionToString(m_car.GetDirection()) << std::endl;
	m_output << "Current speed: " << m_car.GetSpeed() << std::endl;
	m_output << "Current gear: " << GearToString(m_car.GetGear()) << std::endl;
	m_output << std::endl;
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
	m_output << std::endl;
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
	m_output << std::endl;
}

void CController::ExecuteSetGearCommand(int value)
{
	auto gear = IntToGear(value);
	if (gear.has_value() && m_car.SetGear(gear.value()))
	{
		m_output << "The gear is set to " + std::to_string(value) << std::endl;
	}
	else
	{
		m_output << "It is not possible to set the gear to " + std::to_string(value) << std::endl;
	}
	m_output << std::endl;
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
	m_output << std::endl;
}

void CController::ExecuteHelpCommand()
{
	auto indent = std::string(5, ' ');
	m_output << "The following commands are available: " << std::endl;
	m_output << indent << "- Help - show available commands" << std::endl;
	m_output << indent << "- Info - information about the state a car" << std::endl;
	m_output << indent << "- EngineOn - turning on the engines" << std::endl;
	m_output << indent << "- EngineOff - turning off the engines" << std::endl;
	m_output << indent << "- SetGear <-1, 0, 1, 2, 3, 4, 5> - setting up the gear" << std::endl;
	m_output << indent << "- SetSpeed <int> - setting the speed" << std::endl;
	m_output << indent << "- Exit - exiting the program" << std::endl;
	m_output << std::endl;
}

void CController::ExecuteUnknownCommand(const std::string& msgError)
{
	m_output << msgError << std::endl;
	m_output << std::endl;
	ExecuteHelpCommand();
}

std::string CController::DirectionToString(CCar::Direction direction)
{
	switch (direction)
	{
	case CCar::Direction::NO_MOVEMENT:
		return "No movement";
	case CCar::Direction::FORWARD:
		return "Moving forward";
	case CCar::Direction::BACK:
		return "Moving back";
	default:
		return "Unknown car condition";
	}
}

std::string CController::GearToString(CCar::Gear gear)
{
	switch (gear)
	{
	case CCar::Gear::REVERSE:
		return "Reverse";
	case CCar::Gear::NEUTRAL:
		return "Neutral";
	case CCar::Gear::FIRST:
		return "First";
	case CCar::Gear::SECOND:
		return "Second";
	case CCar::Gear::THIRD:
		return "Third";
	case CCar::Gear::FOURTH:
		return "Fourth";
	case CCar::Gear::FIFTH:
		return "Fifth";
	default:
		return "Unknown gear";
	}
}

std::optional<CCar::Gear> CController::IntToGear(int value)
{
	switch (value)
	{
	case -1:
		return CCar::Gear::REVERSE;
	case 0:
		return CCar::Gear::NEUTRAL;
	case 1:
		return CCar::Gear::FIRST;
	case 2:
		return CCar::Gear::SECOND;
	case 3:
		return CCar::Gear::THIRD;
	case 4:
		return CCar::Gear::FOURTH;
	case 5:
		return CCar::Gear::FIFTH;
	default:
		return std::nullopt;
	}
}
