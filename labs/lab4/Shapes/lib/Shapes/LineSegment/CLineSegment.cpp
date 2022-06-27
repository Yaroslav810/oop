#include "CLineSegment.h"

CLineSegment::CLineSegment(CPoint start, CPoint end, uint32_t color)
	: m_startPoint(start)
	, m_endPoint(end)
	, m_outlineColor(color)
{
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	double dx = m_endPoint.GetX() - m_startPoint.GetX();
	double dy = m_endPoint.GetY() - m_startPoint.GetY();
	return std::sqrt(dx * dx + dy * dy);
}

std::string CLineSegment::ToString() const
{
	std::stringstream ss;
	ss << std::fixed
	   << std::setprecision(2)
	   << "Type: line segment" << std::endl
	   << "Start point: " << m_startPoint.ToString() << std::endl
	   << "End point: " << m_endPoint.ToString() << std::endl
	   << "Area: " << GetArea() << std::endl
	   << "Perimeter: " << GetPerimeter() << std::endl
	   << "Outline color: " << std::setfill('0') << std::setw(6) << std::hex << GetOutlineColor() << std::dec << std::endl;
	return ss.str();
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}
