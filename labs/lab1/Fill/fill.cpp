#include "stdafx.h"

const int MAX_COLUMNS = 100;
const int MAX_ROWS = 100;

const char EMPTINESS = ' ';
const char BORDER = '#';
const char START_POSITION = 'O';
const char FILL = '-';

using Field = char[MAX_ROWS][MAX_COLUMNS];

struct Args
{
	std::string input;
	std::string output;
};

std::string buildInvalidArgcError()
{
	return "Invalid argument count"
		   "\n"
		   "Usage: fill.exe <inputFile> <outputFile>";
}

std::string buildFileReadingError()
{
	return "Error reading the file!"
		   "\n"
		   "It is possible that the file is corrupted or there are no permissions to read it"
		   "\n";
}

std::string buildFileWritingError()
{
	return "Error writing the file!"
		   "\n"
		   "It is possible that the file is corrupted or there are no permissions to write it"
		   "\n";
}

Args parseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		throw std::invalid_argument(buildInvalidArgcError());
	}

	return {
		.input = argv[1],
		.output = argv[2]
	};
}

void initField(Field field)
{
	for (int i = 0; i < MAX_ROWS; ++i)
	{
		for (int j = 0; j < MAX_COLUMNS; ++j)
		{
			field[i][j] = EMPTINESS;
		}
	}
}

void readFieldFromFile(std::ifstream& in, Field field)
{
	int rowCount = 0;

	std::string str;
	while (std::getline(in, str) && rowCount < MAX_ROWS)
	{
		for (int i = 0; i < str.length(); ++i)
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
			case '\n':
				break;
			default:
				std::cout << rowCount << ":" << i << std::endl;
				throw std::invalid_argument("Unknown character: " + std::string(1, str[i]) + "\n");
			}
		}

		rowCount++;
	}
}

void printField(std::ofstream& out, Field field)
{
	for (int i = 0; i < MAX_ROWS; ++i)
	{
		for (int j = 0; j < MAX_COLUMNS; ++j)
		{
			out << field[i][j];
		}

		out << std::endl;
	}
}

void fillFieldInputData(std::ifstream& in, Field field)
{
	initField(field);
	readFieldFromFile(in, field);
}

void fillAreaAroundPosition(Field field, const int row, const int column)
{
	if (field[row][column] == EMPTINESS)
	{
		field[row][column] = FILL;
	}

	if (row > 0 && field[row - 1][column] == EMPTINESS)
	{
		fillAreaAroundPosition(field, row - 1, column);
	}
	if (row < MAX_ROWS && field[row + 1][column] == EMPTINESS)
	{
		fillAreaAroundPosition(field, row + 1, column);
	}
	if (column > 0 && field[row][column - 1] == EMPTINESS)
	{
		fillAreaAroundPosition(field, row, column - 1);
	}
	if (column < MAX_COLUMNS && field[row][column + 1] == EMPTINESS)
	{
		fillAreaAroundPosition(field, row, column + 1);
	}
}

void fillArea(Field field)
{
	for (int i = 0; i < MAX_ROWS; ++i)
	{
		for (int j = 0; j < MAX_COLUMNS; ++j)
		{
			if (field[i][j] == START_POSITION)
			{
				fillAreaAroundPosition(field, i, j);
			}
		}
	}
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = parseArgs(argc, argv);

		std::ifstream input;
		input.open(args.input);
		if (!input.is_open())
		{
			throw std::ios_base::failure(buildFileReadingError());
		}

		std::ofstream output;
		output.open(args.output);
		if (!output.is_open())
		{
			throw std::ios_base::failure(buildFileWritingError());
		}

		Field field = {};
		fillFieldInputData(input, field);

		if (input.bad())
		{
			throw std::ios_base::failure(buildFileReadingError());
		}

		fillArea(field);
		printField(output, field);

		if (!output.flush())
		{
			throw std::ios_base::failure(buildFileWritingError());
		}
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	catch (const std::ios_base::failure& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
