#include "../include/data_loader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace projectname {

// Base class constructor definition
DataLoader::DataLoader(const string& file) : filename(file) {}

// Safe data access getter
const vector<vector<string>>& DataLoader::getData() const {
    return table;
}

// Derived class polymorphic implementation for parsing CSV data
void CsvDataLoader::load() {
    table.clear(); // Clear any existing data
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        throw runtime_error("Could not open CSV file: " + filename);
    }

    string line;
    while (getline(inputFile, line)) {
        vector<string> row;
        string cell;
        stringstream lineStream(line);

        while (getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }

        // Handle trailing empty cells (e.g., if a line ends with a comma)
        if (!line.empty() && line.back() == ',') {
            row.push_back("");
        }

        table.push_back(row);
    }
}

} // namespace projectname