#pragma once
#include "IShape.h"

class CShape : public IShape
{
public:
	explicit CShape(uint32_t outlineColor);
	[[nodiscard]] virtual uint32_t GetOutlineColor() const = 0;

private:
	uint32_t m_outlineColor;
};
