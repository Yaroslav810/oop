#pragma once
#include "./../../../Point/CPoint.h"
#include "./../CSolidShape.h"
#include <iomanip>

class CRectangle : public CSolidShape
{
public:
	CRectangle(CPoint leftTop, CPoint rightBottom, uint32_t outlineColor, uint32_t fillColor);
	CRectangle(CPoint leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor);

	[[nodiscard]] CPoint GetLeftTop() const;
	[[nodiscard]] CPoint GetRightBottom() const;
	[[nodiscard]] double GetWidth() const;
	[[nodiscard]] double GetHeight() const;

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;

private:
	CPoint m_leftTop;
	CPoint m_rightBottom;
};
