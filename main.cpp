#include "solution.h"

int main() {
    // File paths
    std::string inputFilename = "/Users/ahmed.mokhtar/Documents/NavViz/C++ Challenge/input/test1.csv";
    std::string outputFilename = "/Users/ahmed.mokhtar/Documents/NavViz/C++ Challenge/output/test1.csv";

    // Read the data from the input CSV file (can be int or double)
    auto data = readCSV<double>(inputFilename);

    // Process the data (interpolate bad values)
    interpolateBadValues(data);

    // Write the processed data to the output CSV file
    writeCSV(outputFilename, data);

    std::cout << "CSV file processed and saved to " << outputFilename << std::endl;

    return 0;
}
