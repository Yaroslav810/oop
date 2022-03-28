#pragma once
#include "stdafx.h"
#include "Direction.h"

using TransmissionSpeedRanges = std::map<int, std::pair<int, int>>;

class CCar
{
public:
	CCar();
	~CCar();

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	TransmissionSpeedRanges m_transmissionSpeedRanges;
	TransmissionSpeedRanges InitTransmissionSpeedRanges();

	bool m_isEngineTurnOn;
	int m_currentSpeed;
	int m_currentGear;
};
