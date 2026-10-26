#ifndef DATAVIZ_COUNTPLOT_HPP
#define DATAVIZ_COUNTPLOT_HPP

#include <cstddef>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace dataviz {

class Plot {
protected:
    std::string title_;

public:
    explicit Plot(const std::string& title)
        : title_(title) {}

    virtual ~Plot() = default;

    virtual std::string summary() const = 0;
};

class CountPlot : public Plot {
private:
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