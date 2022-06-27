#include "CShapeController.h"
#include <iostream>

int main()
{
	try
	{
		CShapeController controller;
		controller.Start(std::cin, std::cout);
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
