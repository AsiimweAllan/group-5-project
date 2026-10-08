#ifndef DATA_LOADER_HPP
#define DATA_LOADER_HPP

#include <vector>
#include <string>

namespace projectname {

    // This tells the rest of the team's files that your loading function exists
    std::vector<std::vector<std::string>> load_csv_data(const std::string& filename);

} // namespace projectname

#endif // DATA_LOADER_HPP