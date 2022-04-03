#include "stdafx.h"
#include "CCarController.h"

int main()
{
	CCar car;
	CCarController controller(car, std::cin, std::cout);
	controller.Start();

	return 0;
}
