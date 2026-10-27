#include "CountPlot.hpp"
#include <string>

namespace survey {

// Constructor sets up the title and saves the votes
CountPlot::CountPlot(std::vector<std::string> categories)
    : Plot("Campus Survey Count Plot"), categories_(categories) {}

// here, the counting of how many times each thing shows up is done using  std::map to know exactly by name
std::map<std::string, std::size_t> CountPlot::counts() const {
    std::map<std::string, std::size_t> frequency_map; // frequency map is where the program keeps track of how often each value appears

    // counts each item on the list
    for (const std::string& category : categories_) { 
        frequency_map[category]++;
    }

    return frequency_map;
}

// make a  summary of the counts
std::string CountPlot::summary() const {
    std::string result = "--- " + title_ + " ---\n";
    
    // get the counted map from our other function instead of counting again
    std::map<std::string, std::size_t> freq_map = counts();

    // Loop through the map and append, add each item one by one otno the next line right at its bottom
    for (const auto& pair : freq_map) {
        result += pair.first + ": " + std::to_string(pair.second) + "\n";
    }

    return result;
}

} 