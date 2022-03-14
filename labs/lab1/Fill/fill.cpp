#include "stdafx.h"

const int MAX_COLUMNS = 100;
const int MAX_ROWS = 100;

const char EMPTINESS = ' ';
const char BORDER = '#';
const char START_POSITION = 'O';
const char FILL = '-';

using Field = std::array<std::array<char, MAX_COLUMNS>, MAX_ROWS>;

struct Args
{
	std::string input;
	std::string output;
};

struct Cell
{
	size_t i;
	size_t j;
};

std::string BuildInvalidArgcError()
{
	return "Invalid argument count"
		   "\n"
		   "Usage: fill.exe <inputFile> <outputFile>";
}

std::string BuildFileReadingError()
{
	return "Error reading the file!"
		   "\n"
		   "It is possible that the file is corrupted or there are no permissions to read it"
		   "\n";
}

std::string BuildFileWritingError()
{
	return "Error writing the file!"
		   "\n"
		   "It is possible that the file is corrupted or there are no permissions to write it"
		   "\n";
}

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		throw std::invalid_argument(BuildInvalidArgcError());
	}

	return {
		.input = argv[1],
		.output = argv[2]
	};
}

Field InitField()
{
	Field field = {};
	for (size_t i = 0; i < MAX_ROWS; ++i)
	{
		for (size_t j = 0; j < MAX_COLUMNS; ++j)
		{
			field[i][j] = EMPTINESS;
		}
	}

	return field;
}

void ReadFieldFromFile(std::istream& in, Field& field)
{
	size_t rowCount = 0;

	std::string str;
	while (std::getline(in, str) && rowCount < MAX_ROWS)
	{
		for (size_t i = 0; i < str.length(); ++i)
		{
			if (i > MAX_COLUMNS)
			{
				break;
			}

			switch (str[i])
			{
			case EMPTINESS:
			case BORDER:
			case START_POSITION:
				field[rowCount][i] = str[i];
				continue;
			default:
				throw std::invalid_argument("Unknown character: " + std::string(1, str[i]) + "\n");
			}
		}

		rowCount++;
	}
}

void PrintFieldToStream(std::ostream& out, const Field& field)
{
	for (size_t i = 0; i < MAX_ROWS; ++i)
	{
		for (size_t j = 0; j < MAX_COLUMNS; ++j)
		{
			out << field[i][j];
		}

		out << std::endl;
	}
}

void PrintFieldToFile(const std::string& outputFile, const Field& field)
{
	std::ofstream output;
	output.open(outputFile);
	if (!output.is_open())
	{
		throw std::ios_base::failure(BuildFileWritingError());
	}

	PrintFieldToStream(output, field);

	if (!output.flush())
	{
		throw std::ios_base::failure(BuildFileWritingError());
	}
}

Field GetFieldFromFile(const std::string& inputFile)
{
	std::ifstream input;
	input.open(inputFile);
	if (!input.is_open())
	{
		throw std::ios_base::failure(BuildFileReadingError());
	}

	auto field = InitField();
	ReadFieldFromFile(input, field);
	if (input.bad())
	{
		throw std::ios_base::failure(BuildFileReadingError());
	}

	return field;
}

void FillTopNeighboringCellIfEmpty(Field& field, std::queue<Cell>& queue, const size_t row, const size_t column)
{
	if (row > 0 && field[row - 1][column] == EMPTINESS)
	{
		field[row - 1][column] = FILL;
		queue.push({
			.i =  row - 1,
			.j = column
		});
	}
}

void FillBottomNeighboringCellIfEmpty(Field& field, std::queue<Cell>& queue, const size_t row, const size_t column)
{
	if (row < MAX_ROWS && field[row + 1][column] == EMPTINESS)
	{
		field[row + 1][column] = FILL;
		queue.push({
			.i =  row + 1,
			.j = column
		});
	}
}

void FillLeftNeighboringCellIfEmpty(Field& field, std::queue<Cell>& queue, const size_t row, const size_t column)
{
	if (column > 0 && field[row][column - 1] == EMPTINESS)
	{
		field[row][column - 1] = FILL;
		queue.push({
			.i =  row,
			.j = column - 1
		});
	}
}

void FillRightNeighboringCellIfEmpty(Field& field, std::queue<Cell>& queue, const size_t row, const size_t column)
{
	if (column < MAX_COLUMNS && field[row][column + 1] == EMPTINESS)
	{
		field[row][column + 1] = FILL;
		queue.push({
			.i =  row,
			.j = column + 1
		});
	}
}

void FillNeighboringCell(Field& field, std::queue<Cell>& queue, const size_t row, const size_t column)
{
	if (field[row][column] == EMPTINESS)
	{
		field[row][column] = FILL;
	}

	FillTopNeighboringCellIfEmpty(field, queue, row, column);
	FillBottomNeighboringCellIfEmpty(field, queue, row, column);
	FillLeftNeighboringCellIfEmpty(field, queue, row, column);
	FillRightNeighboringCellIfEmpty(field, queue, row, column);
}

void PushStartPositionToQueue(Field& field, std::queue<Cell>& queue)
{
	for (size_t i = 0; i < MAX_ROWS; ++i)
	{
		for (size_t j = 0; j < MAX_COLUMNS; ++j)
		{
			if (field[i][j] == START_POSITION)
			{
				queue.push({ i, j });
			}
		}
	}
}

void FillArea(Field& field)
{
	std::queue<Cell> queue = {};
	PushStartPositionToQueue(field, queue);
	while (!queue.empty())
	{
		auto front = queue.front();
		FillNeighboringCell(field, queue, front.i, front.j);
		queue.pop();
	}
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);
		auto field = GetFieldFromFile(args.input);
		FillArea(field);
		PrintFieldToFile(args.output, field);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
