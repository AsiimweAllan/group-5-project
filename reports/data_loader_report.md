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

week 3

• Encapsulation: The raw file data (table) and the path (filename) are hidden from direct external modification inside the DataLoader class using protected access specifiers. The data can only be read externally using the public method getData().
• Inheritance: CsvDataLoader inherits all properties and access rules from DataLoader via public inheritance (class CsvDataLoader : public DataLoader).
• Polymorphism: The load() function is declared as a pure virtual function (= 0) in the base class. It is polymorphically overridden (override) in CsvDataLoader to handle specific CSV syntax. This allows you to handle multiple parser types (like JSON or XML) using a single base pointer











