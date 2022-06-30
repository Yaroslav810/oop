#pragma once
#include "../../../Point/CPoint.h"
#include "../CSolidShape.h"
#include <cmath>
#include <iomanip>

class CCircle : public CSolidShape
{
public:
	CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor);

	[[nodiscard]] CPoint GetCenter() const;
	[[nodiscard]] double GetRadius() const;

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;

private:
	CPoint m_center;
	double m_radius;
};
