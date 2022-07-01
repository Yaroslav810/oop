#include "CTriangle.h"

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, CShape(outlineColor)
	, CSolidShape(fillColor)
{
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

double CTriangle::GetArea() const
{
	auto halfPerimeter = GetPerimeter() * 0.5;
	return std::sqrt(halfPerimeter * (halfPerimeter - std::hypot(m_vertex1.GetX() - m_vertex2.GetX(), m_vertex1.GetY() - m_vertex2.GetY()))
		* (halfPerimeter - std::hypot(m_vertex2.GetX() - m_vertex3.GetX(), m_vertex2.GetY() - m_vertex3.GetY()))
		* (halfPerimeter - std::hypot(m_vertex3.GetX() - m_vertex1.GetX(), m_vertex3.GetY() - m_vertex1.GetY())));
}

double CTriangle::GetPerimeter() const
{
	return std::hypot(m_vertex1.GetX() - m_vertex2.GetX(), m_vertex1.GetY() - m_vertex2.GetY())
		+ std::hypot(m_vertex2.GetX() - m_vertex3.GetX(), m_vertex2.GetY() - m_vertex3.GetY())
		+ std::hypot(m_vertex3.GetX() - m_vertex1.GetX(), m_vertex3.GetY() - m_vertex1.GetY());
}

std::string CTriangle::ToString() const
{
	std::stringstream ss;
	ss << std::fixed
	   << std::setprecision(2)
	   << "Type: triangle" << std::endl
	   << "Vertex 1: " << m_vertex1.ToString() << std::endl
	   << "Vertex 2: " << m_vertex2.ToString() << std::endl
	   << "Vertex 3: " << m_vertex3.ToString() << std::endl
	   << "Area: " << GetArea() << std::endl
	   << "Perimeter: " << GetPerimeter() << std::endl
	   << "Outline color: " << std::setfill('0') << std::setw(6) << std::hex << GetOutlineColor() << std::endl
	   << "Fill  color: " << std::setfill('0') << std::setw(6) << GetFillColor() << std::dec << std::endl;

	return ss.str();
}
