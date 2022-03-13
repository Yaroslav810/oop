#include "stdafx.h"

std::optional<std::vector<double>> readNumbers(std::istream& in) {
	std::vector<double> numbers = {};

	double number;
	while (in >> number) {
		numbers.push_back(number);
	}

	return {numbers};
}

void printNumbers(std::ostream& out, std::vector<double> numbers) {

}



int main()
{
	auto numbers = readNumbers(std::cin);
	if (!numbers.has_value()) {
		throw std::invalid_argument("");
	}

	//copy(istream_iterator<double>(cin), istream_iterator<double>(), back_inserter(numbers));


	/*
	for (auto number : numbers)
	{
		cout << number << ", ";
	}
	*/
	copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, ", "));

	cout << "\nSize of vector: " << numbers.size() << "\n";
	return 0;
}

