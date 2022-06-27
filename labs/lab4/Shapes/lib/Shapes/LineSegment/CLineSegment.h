#pragma once
#include "../../Point/CPoint.h"
#include "../IShape.h"
#include <cmath>
#include <iomanip>

class CLineSegment : public IShape
{
public:
	CLineSegment(CPoint start, CPoint end, uint32_t color);

	[[nodiscard]] CPoint GetStartPoint() const;
	[[nodiscard]] CPoint GetEndPoint() const;

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	uint32_t m_outlineColor;
};
