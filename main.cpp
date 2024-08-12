#include "solution.h"


int main(int argc, char* argv[]) {
    // Check if the correct number of arguments are provided
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    // File paths from command-line arguments
    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];
    // Read the data from the input CSV file (can be int or double)
    auto data = readCSV<double>(inputFilename);

    // Process the data (interpolate bad values)
    interpolateBadValues(data);

    // Write the processed data to the output CSV file
    writeCSV(outputFilename, data);

    std::cout << "CSV file processed and saved to " << outputFilename << std::endl;

    return 0;
}
