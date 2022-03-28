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
