#ifndef DATAVIZ_COUNTPLOT_HPP
#define DATAVIZ_COUNTPLOT_HPP

#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace dataviz {

struct Color {
    std::uint8_t r{70}, g{130}, b{180};
};

class Plot {
protected:
    std::string x_label_ = "Category";
    std::string y_label_ = "Count";
    std::string title_ = "Count Plot";

public:
    virtual ~Plot() = default;

    void setXLabel(const std::string& label) { x_label_ = label; }
    void setYLabel(const std::string& label) { y_label_ = label; }
    void setTitle(const std::string& title) { title_ = title; }

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
    explicit CountPlot(std::vector<std::string> categories)
        : categories_(std::move(categories)) {}

    std::map<std::string, std::size_t> counts() const;

    std::string summary() const override;

    std::string renderSVG(
        int width = 800,
        int height = 500
    ) const override;

    void setBarColor(Color color) { bar_color_ = color; }
};

} // namespace dataviz

#endif // DATAVIZ_COUNTPLOT_HPP