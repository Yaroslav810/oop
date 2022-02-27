#include <iostream>
#include <fstream>
#include <optional>
#include <string>

struct Args {
    std::string inputFileName;
    std::string outputFileName;
};

std::optional<Args> parseArgs(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Invalid arguments count" << std::endl;
        std::cout << "Usage: copyfile-my.exe <input> <output>" << std::endl;
        return std::nullopt;
    }

    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    return args;
}

void copyStreams(std::ifstream& input, std::ofstream& output) {
    char ch;
    while (input.get(ch)) {
        if (!output.put(ch)) {
            break;
        }
    }
}

int main(int argc, char* argv[]) {

    auto args = parseArgs(argc, argv);
    if (!args) {
        return 1;
    }

    std::ifstream input;
    input.open(args->inputFileName);
    if (!input.is_open()) {
        std::cout << "Failed to open " << args->inputFileName << " for reading!" << std::endl;
        return 1;
    }

    std::ofstream output;
    output.open(args->outputFileName);
    if (!output.is_open()) {
        std::cout << "Failed to open " << args->outputFileName << " for writing!" << std::endl;
        return 1;
    }

    copyStreams(input, output);

    if (input.bad()) {
        std::cout << "Failed to read data from input file" << std::endl;
        return 1;
    }

    if (!output.flush()) {
        std::cout << "Failed to write data to output file" << std::endl;
        return 1;
    }

    return 0;
}
