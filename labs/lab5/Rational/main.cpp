#include "CRational.h"

int main()
{
	CRational number(5);
	std::cout << "number: " << number << std::endl;
	CRational number1(5, 4);
	std::cout << "number1: " << number1 << std::endl;
	CRational number2(10, 20);
	std::cout << "number2: "<< number2 << std::endl;
	std::cout << (number1 + number2) << std::endl;
	std::cout << (number1 + 2) << std::endl;
	std::cout << (2 + number2) << std::endl;
	std::cout << (number1 - number2) << std::endl;
	std::cout << (number1 - 2) << std::endl;
	std::cout << (2 - number2) << std::endl;

	number1 = {1, 2};
	number2 = {1, 6};
	number1 += number2;
	std::cout << "+=: " << number1 << std::endl;
	number1 = {1, 2};
	number1 += 1;
	std::cout << "+=: " << number1 << std::endl;

	number1 = {1, 2};
	number2 = {1, 6};
	number1 -= number2;
	std::cout << "-=: " << number1 << std::endl;
	number1 = {1, 2};
	number1 -= 1;
	std::cout << "-=: " << number1 << std::endl;

	number1 = {1, 2};
	number2 = {2, 3};
	std::cout << (number1 * number2) << std::endl;
	std::cout << (number1 * -3) << std::endl;
	std::cout << (7 * number2) << std::endl;
	std::cout << (number1 / number2) << std::endl;
	std::cout << (number1 / 5) << std::endl;
	std::cout << (7 / number2) << std::endl;

	number1 = {1, 2};
	number2 = {2, 3};
	number1 *= number2;
	std::cout << "*=: " << number1 << std::endl;
	number1 = {1, 2};
	number1 *= 3;
	std::cout << "*=: " << number1 << std::endl;

	number1 = {1, 2};
	number2 = {2, 3};
	number1 /= number2;
	std::cout << "/=: " << number1 << std::endl;
	number1 = {1, 2};
	number1 /= 3;
	std::cout << "/=: " << number1 << std::endl;
	number1 = {3, 4};
	number2 = {3, 8};
	number1 /= number2;
	std::cout << "/=: " << number1 << std::endl;

	return 0;
}
