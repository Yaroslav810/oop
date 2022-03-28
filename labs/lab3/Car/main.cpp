#include "stdafx.h"
#include "CCar.h"
#include "CCarController.h"

int main()
{
	CCar car;
	CController controller(car, std::cin, std::cout);
	controller.Start();

	return 0;
}
