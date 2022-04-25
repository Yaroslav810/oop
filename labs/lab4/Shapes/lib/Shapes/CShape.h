#include "../../stdafx.h"
#include "IShape.h"

class CShape : public IShape
{
public:
	explicit CShape(uint32_t outlineColor);
	[[nodiscard]] uint32_t GetOutlineColor() const override;
private:
	uint32_t m_outlineColor;
};
