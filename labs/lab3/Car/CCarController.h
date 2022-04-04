#include "stdafx.h"
#include "CCar.h"

class CCarController
{
public:
	CCarController(CCar& car, std::istream& input, std::ostream& output);
	void Start();

private:
	enum class CommandType
	{
		INFO,
		ENGINE_ON,
		ENGINE_OFF,
		SET_GEAR,
		SET_SPEED,
		HELP,
		EXIT,
	};
	struct Command
	{
		CommandType type;
		int args;
	};

	Command ParseCommand(const std::string& str);
	std::optional<CommandType> ParseCommandType(const std::string& str);
	int ParseArgs(const std::string& str);
	void ExecuteCommand(const Command& command);
	void ExecuteInfoCommand();
	void ExecuteEngineOnCommand();
	void ExecuteEngineOffCommand();
	void ExecuteSetGearCommand(int value);
	void ExecuteSetSpeedCommand(int value);
	void ExecuteHelpCommand();

	std::string DirectionToString(CCar::Direction direction);
	std::string GearToString(CCar::Gear gear);
	std::optional<CCar::Gear> IntToGear(int value);

	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;
};
