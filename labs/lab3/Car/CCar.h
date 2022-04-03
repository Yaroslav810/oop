#pragma once
#include "stdafx.h"

const int MAX_SPEED_BACK = 20;
const int MAX_SPEED = 150;

class CCar
{
public:
	CCar();
	~CCar();

	enum class Direction
	{
		FORWARD,
		BACK,
		NO_MOVEMENT,
	};

	enum class Gear
	{
		REVERSE = -1,
		NEUTRAL,
		FIRST,
		SECOND,
		THIRD,
		FOURTH,
		FIFTH,
	};

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	Gear GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(Gear gear);
	bool SetSpeed(int speed);

private:
	using TransmissionSpeedRanges = std::map<Gear, std::pair<int, int>>;
	TransmissionSpeedRanges m_transmissionSpeedRanges;
	TransmissionSpeedRanges InitTransmissionSpeedRanges();

	void SetDirection(int speed);

	Direction m_direction;
	bool m_isEngineTurnOn;
	int m_currentSpeed;
	Gear m_currentGear;
};
