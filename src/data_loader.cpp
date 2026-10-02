#include<iostream>
#include <vector>          // Needed to make our grid list
#include <string>          // Needed for text structures

namespace projectname {

// 2. This function creates a simple text grid to store our data rows and columns
std::vector<std::vector<std::string>> load_csv_data(const std::string& filename) {
    
    // Create a grid (a list that will hold all our rows together)
    std::vector<std::vector<std::string>> data_grid;

    // Create simple text variables to hold data while we process it
    std::string row;     // Will hold one whole horizontal row of text from the file
    std::string column;  // Will hold one single column piece (word or number) at a time

    // [Note for Next Time]: We will add the logic to fill the grid here.

    // 3. Return the spreadsheet grid back to the team
    return data_grid;
}

} // namespace projectname=`