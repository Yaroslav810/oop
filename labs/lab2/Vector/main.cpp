#include "vector.h"

int main()
{
	auto numbers = ReadDoubleVector(std::cin);
	if (!numbers.has_value()) {
		std::cout << "Error parsing data!" << std::endl;
		return 1;
	}

	MultiplyArrayElementsByMinimumElement(numbers.value());
	SortVector(numbers.value());
	PrintNumbers(std::cout, numbers.value());
	return 0;
}
