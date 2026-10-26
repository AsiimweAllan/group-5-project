#ifndef DATA_LOADER_HPP
#define DATA_LOADER_HPP

#include <string>
#include <vector>

namespace projectname {

class DataLoader {
protected: // <-- CRITICAL: Must be protected, NOT private
    std::string filename;
    std::vector<std::vector<std::string>> table; // Fixed: Added std:: to the inner vector

public:
    explicit DataLoader(const std::string& file);
    virtual ~DataLoader() = default;

    virtual void load() = 0;
    const std::vector<std::vector<std::string>>& getData() const;
};

class CsvDataLoader : public DataLoader {
public:
    using DataLoader::DataLoader;
    void load() override; // Overrides the load function
};

} // namespace projectname

#endif