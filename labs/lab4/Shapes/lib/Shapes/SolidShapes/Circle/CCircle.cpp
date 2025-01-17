#include "CCircle.h"

CCircle::CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor)
	: m_center(center)
	, m_radius(radius)
	, CShape(outlineColor)
	, CSolidShape(fillColor)
{
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

double CCircle::GetArea() const
{
	return M_PI * GetRadius() * GetRadius();
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * GetRadius();
}

std::string CCircle::ToString() const
{
	std::stringstream ss;
	ss << std::fixed
	   << std::setprecision(2)
	   << "Type: circle" << std::endl
	   << "Center: " << GetCenter().ToString() << std::endl
	   << "Radius: " << GetRadius() << std::endl
	   << "Area: " << GetArea() << std::endl
	   << "Perimeter: " << GetPerimeter() << std::endl
	   << "Outline color: " << std::setfill('0') << std::setw(6) << std::hex << GetOutlineColor() << std::endl
	   << "Fill  color: " << std::setfill('0') << std::setw(6) << GetFillColor() << std::dec << std::endl;

	return ss.str();
}
