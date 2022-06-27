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
	CShapeController();
	void Start(std::istream& input, std::ostream& output);

private:
	using ShapePtr = std::shared_ptr<IShape>;
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

	static ShapeVector ReadShapes(std::istream& input);

	static Command ParseCommand(const std::string& str);
	static std::optional<CommandType> ParseCommandType(const std::string& command);
	static ShapePtr GetShape(const Command& command);
	static ShapePtr CreateLine(const std::string& str);
	static ShapePtr CreateCircle(const std::string& str);
	static ShapePtr CreateRectangle(const std::string& str);
	static ShapePtr CreateTriangle(const std::string& str);
	static ShapePtr NoneCommand(const std::string& str);

	static double ReadDouble(std::istream& input);
	static CPoint ReadPoint(std::istream& input);
	static uint32_t ReadColor(std::istream& input);

	ShapeVector m_shapes;
};
