#ifndef DATAVIZ_COUNTPLOT_HPP
#define DATAVIZ_COUNTPLOT_HPP

#include <cstddef>
#include <map>
#include <string>
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

    std::map<std::string, std::size_t> counts() const;

    std::string summary() const override;
};

}

#endif