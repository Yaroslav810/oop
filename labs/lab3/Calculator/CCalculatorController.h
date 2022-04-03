#include "stdafx.h"
#include "CCalculator.h"

class CCalculatorController
{
public:
	CCalculatorController(CCalculator& car, std::istream& input, std::ostream& output);
	~CCalculatorController();

private:
	CCalculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;
};
