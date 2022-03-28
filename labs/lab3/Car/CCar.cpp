#include "CCar.h"

CCar::CCar()
	: m_isEngineTurnOn(false)
	, m_currentSpeed(0)
	, m_currentGear(0)
	, m_transmissionSpeedRanges(InitTransmissionSpeedRanges())
{
}

CCar::~CCar()
{
}

TransmissionSpeedRanges CCar::InitTransmissionSpeedRanges()
{
	return {
		{ -1, std::make_pair(-20, 0) },
		{ 0, std::make_pair(-20, 150) },
		{ 1, std::make_pair(0, 30) },
		{ 2, std::make_pair(20, 50) },
		{ 3, std::make_pair(30, 60) },
		{ 4, std::make_pair(40, 90) },
		{ 5, std::make_pair(50, 150) }
	};
}

bool CCar::IsTurnedOn() const
{
	return m_isEngineTurnOn;
}

Direction CCar::GetDirection() const
{
	if (m_currentSpeed > 0)
	{
		return Direction::FORWARD;
	}

	if (m_currentSpeed < 0)
	{
		return Direction::BACK;
	}

	return Direction::NO_MOVEMENT;
}

int CCar::GetSpeed() const
{
	return abs(m_currentSpeed);
}

int CCar::GetGear() const
{
	return m_currentGear;
}

bool CCar::TurnOnEngine()
{
	m_isEngineTurnOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (m_currentSpeed == 0 && m_currentGear == 0)
	{
		m_isEngineTurnOn = false;
	}

	return !m_isEngineTurnOn;
}

bool CCar::SetGear(int gear)
{
	if (gear == -1)
	{
		if (m_currentGear == -1 || m_currentSpeed == 0)
		{
			m_currentGear = gear;
			return true;
		}

		return false;
	}

	if (gear == 0)
	{
		m_currentGear = gear;
		return true;
	}

	if (gear == 1 && m_currentSpeed < 0)
	{
		return false;
	}

	if (auto it = m_transmissionSpeedRanges.find(gear);
		it != m_transmissionSpeedRanges.end())
	{
		if (m_currentSpeed >= it->second.first && m_currentSpeed <= it->second.second)
		{
			m_currentGear = gear;
			return true;
		}
	}

	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (speed < 0 || !m_isEngineTurnOn)
	{
		return false;
	}

	if (m_currentGear == 0 && abs(m_currentSpeed) < speed)
	{
		return false;
	}

	if (m_currentGear == -1)
	{
		speed *= -1;
	}

	if (auto it = m_transmissionSpeedRanges.find(m_currentGear);
		it != m_transmissionSpeedRanges.end())
	{
		if (speed >= it->second.first && speed <= it->second.second)
		{
			m_currentSpeed = speed;
			return true;
		}
	}

	return false;
}
