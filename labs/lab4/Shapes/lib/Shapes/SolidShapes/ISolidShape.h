#pragma once
#include "../IShape.h"

class ISolidShape : public IShape
{
	[[nodiscard]] virtual uint32_t GetFillColor() const = 0;
};

// TODO: CSolidShape
