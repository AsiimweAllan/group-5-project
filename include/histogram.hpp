#ifndef DATAVIZ_HISTOGRAM_HPP
#define DATAVIZ_HISTOGRAM_HPP

#include <cstddef>
#include <map>
#include <string>
#include <vector>

namespace dataviz {

// A small reusable text histogram for integer-valued observations.
class TextHistogram {
private:
    std::vector<int> data_;

public:
    explicit TextHistogram(const std::vector<int>& data);
    std::map<int, std::size_t> counts() const;
    std::string renderText() const;
};

} // namespace dataviz

#endif // DATAVIZ_HISTOGRAM_HPP
