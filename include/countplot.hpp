#ifndef DATAVIZ_COUNTPLOT_HPP
#define DATAVIZ_COUNTPLOT_HPP
#include <cstddef>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "plot.hpp"
namespace dataviz {
// CountPlot is another kind of Plot and provides its own summary.
class CountPlot : public Plot {
    std::vector<std::string> categories_;
public:
    explicit CountPlot(std::vector<std::string> categories);

    // Original functions (unchanged, other modules may use them).
    std::map<std::string, std::size_t> counts() const;
    std::string summary() const override;

    // New in week 3.
    std::size_t total() const;
    std::string mostCommon() const;
    std::map<std::string, double> percentages() const;
    std::vector<std::pair<std::string, std::size_t>> sortedCounts() const;
    std::string textChart(std::size_t maxWidth = 30) const;
};
}
#endif