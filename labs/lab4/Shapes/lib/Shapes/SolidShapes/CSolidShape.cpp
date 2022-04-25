#include "CSolidShape.h"

CSolidShape::CSolidShape(uint32_t outlineColor, uint32_t fillColor)
	: m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

uint32_t CSolidShape::GetFillColor() const
{
	return 0;
}
