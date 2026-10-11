 Data Loading Component by Akora Sheenaz N
Task: File Reading and Core 2D Grid Structure in C++

1. Objective
The goal of this component is to handle data loading for the project library. It securely opens a specified CSV data file, prevents application crashes using structural file-guard checks, and parses raw comma-separated text into a dynamic two-dimensional data matrix.
 2. Implementation Details
The component is split into two clean architecture files inside the repository:
 `include/data_loader.hpp`: Defines the public namespace and function signature (`load_csv_data`) so it can be called seamlessly by the team.
`src/data_loader.cpp`: Implements the file stream processing logic using `<fstream>` and `<sstream>` to split rows by commas and load them into a `std::vector<std::vector<std::string>>`.

 3. Current Status
File Detection Bug Fixed: The local header inclusion path was updated to `#include "../include/data_loader.hpp"` to correctly link files across the `src/` and `include/` folders.
Compilation Success: The standalone component compiles successfully without any syntax or path errors.