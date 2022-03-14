#pragma once
#include <iostream>
#include <optional>
#include <vector>

std::optional<std::vector<double>> ReadDoubleVector(std::istream& in);

void PrintNumbers(std::ostream& out, const std::vector<double>& numbers);

void MultiplyArrayElementsByMinimumElement(std::vector<double>& vector);
