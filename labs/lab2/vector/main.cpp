#include "vector.h"

int main()
{
	auto numbers = ReadDoubleVector(std::cin);
	if (!numbers.has_value()) {
		throw std::invalid_argument("Error");
	}

	MultiplyArrayElementsByMinimumElement(numbers.value());
	SortVector(numbers.value());
	PrintNumbers(std::cout, numbers.value());
	return 0;
}
