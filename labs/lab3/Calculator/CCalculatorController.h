#include "stdafx.h"
#include "CCalculator.h"

class CCalculatorController
{
public:
	CCalculatorController(CCalculator& car, std::istream& input, std::ostream& output);
	void Start();

private:
	CCalculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;
};
