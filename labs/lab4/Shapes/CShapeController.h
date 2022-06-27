#pragma once
#include "lib/Shapes/LineSegment/CLineSegment.h"
#include "lib/Shapes/SolidShapes/Circle/CCircle.h"
#include "lib/Shapes/SolidShapes/Rectangle/CRectangle.h"
#include "lib/Shapes/SolidShapes/Triangle/CTriangle.h"
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <vector>

class CShapeController
{
public:
	CShapeController(std::istream& input, std::ostream& output);
	void Start();

private:
	using ShapePtr = std::unique_ptr<IShape>;
	using ShapeVector = std::vector<ShapePtr>;

	enum class CommandType
	{
		NONE,
		LINE,
		CIRCLE,
		RECTANGLE,
		TRIANGLE,
	};
	struct Command
	{
		CommandType type;
		std::string arguments;
	};

	ShapeVector ReadShapes();

	static Command ParseCommand(const std::string& str);
	static std::optional<CommandType> ParseCommandType(const std::string& command);
	static ShapePtr GetShape(const Command& command);
	static ShapePtr CreateLine(const std::string& str);
	static ShapePtr CreateCircle(const std::string& str);
	static ShapePtr CreateRectangle(const std::string& str);
	static ShapePtr CreateTriangle(const std::string& str);
	static ShapePtr NoneCommand(const std::string& str);

	void PrintShapeWithMaxArea(const ShapeVector& shapes);
	void PrintShapeWithMinPerimeter(const ShapeVector& shapes);

	static double ReadDouble(std::istream& input);
	static CPoint ReadPoint(std::istream& input);
	static uint32_t ReadColor(std::istream& input);

	std::istream& m_input;
	std::ostream& m_output;
};
