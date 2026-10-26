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
    // Total number of items in the data.
    std::size_t total() const;
    // Category with the highest count (alphabetical first if tied, "" if no data).
    std::string mostCommon() const;
    // Share of each category as a percentage (0 to 100).
    std::map<std::string, double> percentages() const;
    // Categories ordered from highest to lowest count.
    std::vector<std::pair<std::string, std::size_t>> sortedCounts() const;
    // Simple text bar chart, one line per category.
    std::string textChart(std::size_t maxWidth = 30) const;
};
}
#endif
