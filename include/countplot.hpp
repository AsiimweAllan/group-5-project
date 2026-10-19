#ifndef DATAVIZ_COUNTPLOT_HPP
#define DATAVIZ_COUNTPLOT_HPP
#include <cstddef>
#include <map>
#include <string>
#include <vector>
#include "plot.hpp"
namespace dataviz {
// CountPlot is another kind of Plot and provides its own summary.
class CountPlot : public Plot {
    std::vector<std::string> categories_;
public:
    explicit CountPlot(std::vector<std::string> categories);
    std::map<std::string, std::size_t> counts() const;
    std::string summary() const override;
};
}
#endif
