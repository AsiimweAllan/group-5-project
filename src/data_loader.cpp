#include <iostream>
#include "../include/data_loader.hpp" // Successfully fixed path!
#include <vector>          
#include <string>          
#include <fstream>       // For opening and reading files from disk
#include <sstream>       // For splitting text by commas

namespace projectname {

// This function creates a text grid, reads a CSV file, and fills the grid
std::vector<std::vector<std::string>> load_csv_data(const std::string& filename) {
    
    std::vector<std::vector<std::string>> data_grid;
    std::ifstream file(filename);

    // Safety check: Give clear feedback if the file is missing or path is wrong
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file '" << filename << "'. Check the path!" << std::endl;
        return data_grid; 
    }

    std::string row;     
    std::string column;  

    // Read the file line by line (row by row)
    while (std::getline(file, row)) {
        
        std::vector<std::string> current_row_data; 
        std::stringstream row_stream(row);        

        // Extract each column piece separated by a comma
        while (std::getline(row_stream, column, ',')) {
            current_row_data.push_back(column);   
        }

        data_grid.push_back(current_row_data);
    }

    file.close();
    return data_grid;
}

} // namespace projectname