#include <iostream>
#include <optional>
#include <vector>
#include <algorithm>
#include <iomanip>

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
	for (const auto& number : numbers)
	{
		out << std::fixed << std::setprecision(3) << number << " ";
	}
	out << std::endl;
}

void MultiplyArrayElementsByMinimumElement(std::vector<double>& vector)
{
	auto min = *std::min_element(vector.begin(), vector.end());
	std::transform(vector.begin(), vector.end(), vector.begin(), [min](const auto& elem) {
		return elem * min;
	});
}
