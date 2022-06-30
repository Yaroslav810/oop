#pragma once
#include "../CShape.h"

class ISolidShape : public CShape
{
	[[nodiscard]] virtual uint32_t GetFillColor() const = 0;
};
