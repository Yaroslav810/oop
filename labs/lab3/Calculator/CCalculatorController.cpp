#include "CCalculatorController.h"

CCalculatorController::CCalculatorController(CCalculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
{
}

CCalculatorController::~CCalculatorController()
{
}
