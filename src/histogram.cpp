#include "histogram.hpp"

#include <sstream>

namespace dataviz {

TextHistogram::TextHistogram(const std::vector<int>& data) : data_(data) {}

std::map<int, std::size_t> TextHistogram::counts() const {
    std::map<int, std::size_t> result;
    for (const int value : data_) {
        ++result[value];
    }
    return result;
}

std::string TextHistogram::renderText() const {
    std::ostringstream output;
    output << "HISTOGRAM\n---------\n";
    for (const auto& item : counts()) {
        output << item.first << ": ";
        for (std::size_t i = 0; i < item.second; ++i) {
            output << '*';
        }
        output << '\n';
    }
    return output.str();
}

} // namespace dataviz
