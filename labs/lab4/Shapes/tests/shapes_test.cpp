#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../CShapeController.h"
#include <cmath>
#include <limits>

TEST_CASE("Create line")
{
	CPoint startPoint = { -1, 1 };
	CPoint endPoint = { 2, 5 };
	uint32_t outlineColor = 0xff00ff;

	CLineSegment line(startPoint, endPoint, outlineColor);
	REQUIRE(line.GetArea() == 0);
	REQUIRE(line.GetPerimeter() == 5);
	REQUIRE(line.GetOutlineColor() == outlineColor);
}

TEST_CASE("Create rectangle")
{
	CPoint leftTop = { -1, 1 };
	CPoint rightBottom = { 2, 0 };
	uint32_t outlineColor = 0xff00ff;
	uint32_t fillColor = 0x00ff00;

	CRectangle rectangle(leftTop, rightBottom, outlineColor, fillColor);
	REQUIRE(rectangle.GetArea() == 3);
	REQUIRE(rectangle.GetPerimeter() == 8);
	REQUIRE(rectangle.GetOutlineColor() == 0xff00ff);
	REQUIRE(rectangle.GetFillColor() == 0x00ff00);
	REQUIRE(rectangle.GetHeight() == 1);
	REQUIRE(rectangle.GetWidth() == 3);
}

TEST_CASE("Create circle")
{
	CPoint center = { 0, 1 };
	uint32_t outlineColor = 0xff00ff;
	uint32_t fillColor = 0x00ff00;

	CCircle circle(center, 2.5, outlineColor, fillColor);
	REQUIRE(abs(circle.GetArea() - 19.63) <= 0.01);
	REQUIRE(abs(circle.GetPerimeter() - 15.7) <= 0.01);
	REQUIRE(circle.GetOutlineColor() == 0xff00ff);
	REQUIRE(circle.GetFillColor() == 0x00ff00);
	REQUIRE(circle.GetRadius() == 2.5);
}

TEST_CASE("Create triangle")
{
	CPoint vertex1 = { -1, 1 };
	CPoint vertex2 = { 2, 0 };
	CPoint vertex3 = { 3, -3 };
	uint32_t outlineColor = 0xff00ff;
	uint32_t fillColor = 0x00ff00;

	CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);
	REQUIRE(abs(triangle.GetArea() - 4) <= 0.01);
	REQUIRE(abs(triangle.GetPerimeter() - 11.981) <= 0.01);
	REQUIRE(triangle.GetOutlineColor() == 0xff00ff);
	REQUIRE(triangle.GetFillColor() == 0x00ff00);
}

// TODO: PrintShapeWithMaxArea
// TODO: PrintShapeWithMinPerimeter
