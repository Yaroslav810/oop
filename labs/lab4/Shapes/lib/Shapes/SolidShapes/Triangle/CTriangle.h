#pragma once
#include "./../../../Point/CPoint.h"
#include "./../CSolidShape.h"
#include <cmath>
#include <iomanip>

class CTriangle : public CSolidShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor);

	[[nodiscard]] CPoint GetVertex1() const;
	[[nodiscard]] CPoint GetVertex2() const;
	[[nodiscard]] CPoint GetVertex3() const;

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	uint32_t m_outlineColor;
};
