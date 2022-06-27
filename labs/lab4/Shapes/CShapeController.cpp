#include "CShapeController.h"
#include <algorithm>

CShapeController::CShapeController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

void CShapeController::Start()
{
	const auto shapes = ReadShapes();

	PrintShapeWithMaxArea(shapes);
	PrintShapeWithMinPerimeter(shapes);

	for (const auto& d : shapes)
	{
		m_output << std::fixed << std::setprecision(2) << d->ToString() << std::endl;
	}
}

CShapeController::ShapeVector CShapeController::ReadShapes()
{
	std::string str;
	ShapeVector shapes;
	while (std::getline(m_input, str))
	{
		try
		{
			auto command = ParseCommand(str);
			auto shape = GetShape(command);
			if (shape)
			{
				shapes.push_back(std::move(shape));
			}
		}
		catch (const std::exception& e)
		{
			m_output << e.what() << std::endl;
		}
	}

	return shapes;
}

CShapeController::Command CShapeController::ParseCommand(const std::string& str)
{
	std::stringstream line(str);
	std::string type;
	std::string arguments;
	line >> type;
	auto commandType = ParseCommandType(type);
	if (!commandType.has_value())
	{
		return {
			.type = CommandType::NONE,
		};
	}
	line >> std::ws;
	std::getline(line, arguments);
	return {
		.type = commandType.value(),
		.arguments = arguments,
	};
}

std::optional<CShapeController::CommandType> CShapeController::ParseCommandType(const std::string& command)
{
	if (command == "line")
	{
		return CShapeController::CommandType::LINE;
	}
	if (command == "circle")
	{
		return CShapeController::CommandType::CIRCLE;
	}
	if (command == "rectangle")
	{
		return CShapeController::CommandType::RECTANGLE;
	}
	if (command == "triangle")
	{
		return CShapeController::CommandType::TRIANGLE;
	}

	return std::nullopt;
}

CShapeController::ShapePtr CShapeController::GetShape(const CShapeController::Command& command)
{
	switch (command.type)
	{
	case CommandType::LINE:
		return CreateLine(command.arguments);
	case CommandType::CIRCLE:
		return CreateCircle(command.arguments);
	case CommandType::RECTANGLE:
		return CreateRectangle(command.arguments);
	case CommandType::TRIANGLE:
		return CreateTriangle(command.arguments);
	case CommandType::NONE:
		return NoneCommand(command.arguments);
	default:
		throw std::invalid_argument("Undefined state when executing a command");
	}
}

CShapeController::ShapePtr CShapeController::CreateLine(const std::string& str)
{
	std::stringstream ss(str);
	auto const startPoint = ReadPoint(ss);
	auto const endPoint = ReadPoint(ss);
	auto const outlineColor = ReadColor(ss);
	return std::make_unique<CLineSegment>(startPoint, endPoint, outlineColor);
}

CShapeController::ShapePtr CShapeController::CreateCircle(const std::string& str)
{
	std::stringstream ss(str);
	auto centerPoint = ReadPoint(ss);
	auto radius = ReadDouble(ss);
	auto outlineColor = ReadColor(ss);
	auto fillColor = ReadColor(ss);
	return std::make_unique<CCircle>(centerPoint, radius, outlineColor, fillColor);
}

CShapeController::ShapePtr CShapeController::CreateRectangle(const std::string& str)
{
	std::stringstream ss(str);
	auto topLeftPoint = ReadPoint(ss);
	auto width = ReadDouble(ss);
	auto height = ReadDouble(ss);
	auto outlineColor = ReadColor(ss);
	auto fillColor = ReadColor(ss);
	return std::make_unique<CRectangle>(topLeftPoint, width, height, outlineColor, fillColor);
}

CShapeController::ShapePtr CShapeController::CreateTriangle(const std::string& str)
{
	std::stringstream ss(str);
	auto vertex1 = ReadPoint(ss);
	auto vertex2 = ReadPoint(ss);
	auto vertex3 = ReadPoint(ss);
	auto outlineColor = ReadColor(ss);
	auto fillColor = ReadColor(ss);
	return std::make_unique<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
}

void CShapeController::PrintShapeWithMaxArea(const ShapeVector& shapes)
{
	auto const shape = std::max_element(
		shapes.begin(),
		shapes.end(),
		[](const ShapePtr& shape1, const ShapePtr& shape2) {
			return shape1->GetArea() < shape2->GetArea();
		});

	if (shape != shapes.end())
	{
		m_output << "Shape with max area: " << std::endl;
		m_output << (*shape)->ToString() << std::endl;
	}
	else
	{
		m_output << "There is no such element" << std::endl;
	}
}

void CShapeController::PrintShapeWithMinPerimeter(const ShapeVector& shapes)
{
	auto const shape = std::min_element(
		shapes.begin(),
		shapes.end(),
		[](const ShapePtr& shape1, const ShapePtr& shape2) {
			return shape1->GetPerimeter() > shape2->GetPerimeter();
		});

	if (shape != shapes.end())
	{
		m_output << "Shape with min perimeter: " << std::endl;
		m_output << (*shape)->ToString() << std::endl;
	}
	else
	{
		m_output << "There is no such element" << std::endl;
	}
}

double CShapeController::ReadDouble(std::istream& input)
{
	double result;
	input >> result;
	return result;
}

CPoint CShapeController::ReadPoint(std::istream& input)
{
	auto x = ReadDouble(input);
	auto y = ReadDouble(input);
	return { x, y };
}

uint32_t CShapeController::ReadColor(std::istream& input)
{
	uint32_t value;
	input >> std::hex >> value;
	return value;
}

CShapeController::ShapePtr CShapeController::NoneCommand(const std::string& str)
{
	return nullptr;
}
