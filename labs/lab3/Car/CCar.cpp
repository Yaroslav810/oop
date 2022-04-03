#include "CCar.h"

CCar::CCar()
	: m_isEngineTurnOn(false)
	, m_currentSpeed(0)
	, m_currentGear(Gear::NEUTRAL)
	, m_direction(Direction::NO_MOVEMENT)
	, m_transmissionSpeedRanges(InitTransmissionSpeedRanges())
{
}

CCar::~CCar()
{
}

CCar::TransmissionSpeedRanges CCar::InitTransmissionSpeedRanges()
{
	return {
		{ Gear::REVERSE, std::make_pair(0, MAX_SPEED_BACK) },
		{ Gear::NEUTRAL, std::make_pair(0, MAX_SPEED) },
		{ Gear::FIRST, std::make_pair(0, 30) },
		{ Gear::SECOND, std::make_pair(20, 50) },
		{ Gear::THIRD, std::make_pair(30, 60) },
		{ Gear::FOURTH, std::make_pair(40, 90) },
		{ Gear::FIFTH, std::make_pair(50, MAX_SPEED) }
	};
}

bool CCar::IsTurnedOn() const
{
	return m_isEngineTurnOn;
}

CCar::Direction CCar::GetDirection() const
{
	return m_direction;
}

int CCar::GetSpeed() const
{
	return m_currentSpeed;
}

CCar::Gear CCar::GetGear() const
{
	return m_currentGear;
}

bool CCar::TurnOnEngine()
{
	return m_isEngineTurnOn = true;
}

bool CCar::TurnOffEngine()
{
	if (m_currentSpeed == 0 && m_currentGear == Gear::NEUTRAL)
	{
		m_isEngineTurnOn = false;
	}

	return !m_isEngineTurnOn;
}

bool CCar::SetGear(CCar::Gear gear)
{
	if (!m_isEngineTurnOn)
	{
		if (gear == Gear::NEUTRAL)
		{
			m_currentGear = gear;
			return true;
		}

		return false;
	}
	if (gear == Gear::REVERSE)
	{
		if (m_currentGear == Gear::REVERSE || m_currentSpeed == 0)
		{
			m_currentGear = gear;
			return true;
		}

		return false;
	}
	if (gear == Gear::FIRST && m_direction == Direction::BACK)
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
	if (!m_isEngineTurnOn)
	{
		return false;
	}
	if (m_currentGear == Gear::NEUTRAL && speed > m_currentSpeed)
	{
		return false;
	}
	if (auto it = m_transmissionSpeedRanges.find(m_currentGear);
		it != m_transmissionSpeedRanges.end())
	{
		if (speed >= it->second.first && speed <= it->second.second)
		{
			SetDirection(speed);
			m_currentSpeed = speed;
			return true;
		}
	}

	return false;
}

void CCar::SetDirection(int speed)
{
	if (speed == 0)
	{
		m_direction = Direction::NO_MOVEMENT;
	}
	else
	{
		if (m_currentGear == Gear::REVERSE)
		{
			m_direction = Direction::BACK;
		}
		else if (m_currentGear != Gear::NEUTRAL)
		{
			m_direction = Direction::FORWARD;
		}
	}
}
