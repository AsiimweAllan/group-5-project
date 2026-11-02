
#ifndef DATAVIZ_COUNTPLOT_HPP
#define DATAVIZ_COUNTPLOT_HPP

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include "plot.hpp"

namespace dataviz {

struct Color {
    std::uint8_t r, g, b;
};

class CountPlot : public Plot {
private:
    std::vector<std::string> categories_;
    Color bar_color_{70, 130, 180};

public:
    explicit CountPlot(
        const std::vector<std::string>& categories
    );

    std::map<std::string, std::size_t> counts() const;

    std::map<std::string, std::size_t>
    computeFrequencies() const;

    std::string summary() const override;

    std::string renderSVG(
        int width = 800,
        int height = 500
    ) const override;

    void setBarColor(Color color);
};

}

#endif
