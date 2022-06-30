#pragma once
#include "ISolidShape.h"

class CSolidShape : public ISolidShape
{
public:
	explicit CSolidShape(uint32_t fillColor);
	[[nodiscard]] uint32_t GetFillColor() const override;

private:
	uint32_t m_fillColor;
};
