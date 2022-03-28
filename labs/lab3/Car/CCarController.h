#include "stdafx.h"
#include "CCar.h"
#include "Command.h"

class CController
{
public:
	CController(CCar& car, std::istream& input, std::ostream& output);
	~CController();
	void Start();

private:
	Command ParseCommand(const std::string& str);
	CommandType ParseCommandType(const std::string& str);
	int ParseArgs(const std::string& str);
	void ExecuteCommand(const Command& command);
	void ExecuteInfoCommand();
	void ExecuteEngineOnCommand();
	void ExecuteEngineOffCommand();
	void ExecuteSetGearCommand(int value);
	void ExecuteSetSpeedCommand(int value);
	void ExecuteHelpCommand();

	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;
};