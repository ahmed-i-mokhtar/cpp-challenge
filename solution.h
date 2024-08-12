#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>

// A function to read the CSV file and store the data in a 2D vector
template <typename T>
std::vector<std::vector<T>> readCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<T>> data;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<T> row;
        std::istringstream ss(line);
        T value;
        char delim;

        while (ss >> value) {
            row.push_back(value);
            ss >> delim; // Skip the delimiter
        }
        data.push_back(row);
    }

    return data;
}

// Function to perform interpolation for bad values (0)
template <typename T>
void interpolateBadValues(std::vector<std::vector<T>>& data) {
    int rows = data.size();
    int cols = data[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (data[i][j] == 0) {
                int count = 0;
                T sum = 0;

                // Add value from the left
                if (j > 0) {
                    sum += data[i][j-1];
                    ++count;
                }
                // Add value from the right
                if (j < cols-1) {
                    sum += data[i][j+1];
                    ++count;
                }
                // Add value from above
                if (i > 0) {
                    sum += data[i-1][j];
                    ++count;
                }
                // Add value from below
                if (i < rows-1) {
                    sum += data[i+1][j];
                    ++count;
                }

                // Calculate the interpolated value and replace the bad value
                if (count > 0) {
                    data[i][j] = sum / count;
                }
            }
        }
    }
}

// Function to write the processed data to a new CSV file
template <typename T>
void writeCSV(const std::string& filename, const std::vector<std::vector<T>>& data) {
    std::ofstream file(filename);

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << std::fixed << std::setprecision(4) << row[i];
            if (i < row.size() - 1) {
                file << ",";
            }
        }
        file << "\n";
    }
}
