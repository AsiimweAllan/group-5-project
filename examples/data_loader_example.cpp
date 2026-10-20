#include <iostream>
#include <vector>
#include <string>


namespace task_manager{
    std::vector<std::vector<std::string>> fetch_todo_records(){ 

        std::vector<std::vector<std::string>> todo_matrix =
    {
        {"finish math assignments"},
        {"collect my signals work"},
        {"go for discussion"}, 

    };
    return todo_matrix;}
}
int main() {
    // Call the function 
    std::vector<std::vector<std::string>> todo_matrix = task_manager::fetch_todo_records();

    std::cout << "=== My To-Do List ===" << std::endl;
    
    // Loop through and display the data
    for (const auto& single_line : todo_matrix)
     {
        for (const auto& entry_field : single_line) {
            std::cout << "[ ] " << entry_field << std::endl;
        }
    }

    return 0;
}