#include "CPoint.h"

CPoint::CPoint(double x, double y)
	: m_x(x)
	, m_y(y)
{
}

double CPoint::GetX() const
{
	return m_x;
}

double CPoint::GetY() const
{
	return m_y;
}

bool CPoint::operator==(const CPoint& point) const
{
	return (m_x == point.m_x) && (m_y == point.m_y);
}

std::string CPoint::ToString() const
{
	std::string result;
	result.append("{");
	result.append(std::to_string(m_x));
	result.append(", ");
	result.append(std::to_string(m_y));
	result.append("}");
	return result;
}
