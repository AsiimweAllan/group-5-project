
#ifndef DATAVIZ_COUNTPLOT_HPP
#define DATAVIZ_COUNTPLOT_HPP

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace dataviz {

struct Color {
    std::uint8_t r, g, b;
};

class Plot {
protected:
    std::string x_label_ = "Category";
    std::string y_label_ = "Count";
    std::string title_ = "Count Plot";

public:
    virtual ~Plot() = default;

    void setXLabel(const std::string& label);
    void setYLabel(const std::string& label);
    void setTitle(const std::string& title);

    virtual std::string summary() const = 0;

    virtual std::string renderSVG(
        int width = 800,
        int height = 500
    ) const = 0;
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
