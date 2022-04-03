#include "stdafx.h"
#include "CCalculatorController.h"

int main()
{
	CCalculator calculator;
	CCalculatorController calculatorController(calculator, std::cin, std::cout);

	return 0;
}
