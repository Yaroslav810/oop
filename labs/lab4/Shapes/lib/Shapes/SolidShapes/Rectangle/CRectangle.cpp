#include "CRectangle.h"

CRectangle::CRectangle(CPoint leftTop, CPoint rightBottom, uint32_t outlineColor, uint32_t fillColor)
	: m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

CRectangle::CRectangle(CPoint leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor)
	: m_leftTop(leftTop)
	, m_rightBottom(leftTop.GetX() + width, leftTop.GetY() + height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}

double CRectangle::GetWidth() const
{
	return std::abs(m_rightBottom.GetX() - m_leftTop.GetX());
}

double CRectangle::GetHeight() const
{
	return std::abs(m_leftTop.GetY() - m_rightBottom.GetY());
}

double CRectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

double CRectangle::GetPerimeter() const
{
	return 2 * (GetWidth() + GetHeight());
}

std::string CRectangle::ToString() const
{
	std::stringstream ss;
	ss << std::fixed
	   << std::setprecision(2)
	   << "Type: rectangle" << std::endl
	   << "Left top vertex: " << m_leftTop.ToString() << std::endl
	   << "Right bottom vertex: " << m_rightBottom.ToString() << std::endl
	   << "Width: " << GetWidth() << std::endl
	   << "Height: " << GetHeight() << std::endl
	   << "Area: " << GetArea() << std::endl
	   << "Perimeter: " << GetPerimeter() << std::endl
	   << "Outline color: " << std::setfill('0') << std::setw(6) << std::hex << GetOutlineColor() << std::endl
	   << "Fill  color: " << std::setfill('0') << std::setw(6) << GetFillColor() << std::dec << std::endl;

	return ss.str();
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}
