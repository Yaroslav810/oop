#include "CSolidShape.h"
#include "./../CShape.h"

CSolidShape::CSolidShape(uint32_t fillColor)
	: m_fillColor(fillColor)
{
}

uint32_t CSolidShape::GetFillColor() const
{
	return m_fillColor;
}
