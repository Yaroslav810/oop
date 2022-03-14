#include <iostream>
#include <optional>
#include <vector>
#include <iterator>
#include <algorithm>

std::optional<std::vector<double>> ReadDoubleVector(std::istream& in)
{
	std::vector<double> numbers = {};

	double number;
	while (in >> number) {
		numbers.push_back(number);
	}

	if (in.bad()) {
		return std::nullopt;
	}

	return {numbers};
}

void PrintNumbers(std::ostream& out, const std::vector<double>& numbers)
{
	std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(std::cout, " "));
}

void MultiplyArrayElementsByMinimumElement(std::vector<double>& vector)
{
	auto min = *std::min_element(vector.begin(), vector.end());
	std::transform(vector.begin(), vector.end(), vector.begin(), [min](const auto& elem) {
		return elem * min;
	});
}
