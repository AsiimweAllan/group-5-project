#ifndef DATAVIZ_PLOT_HPP
#define DATAVIZ_PLOT_HPP

#include <string>

namespace dataviz {

// Shared interface and common labels for plots in the library.
class Plot {
protected:
    std::string title_;
    std::string x_label_;
    std::string y_label_;

public:
    explicit Plot(const std::string& title = "Plot",
                  const std::string& xLabel = "",
                  const std::string& yLabel = "")
        : title_(title), x_label_(xLabel), y_label_(yLabel) {}

    virtual ~Plot() = default;

    void setTitle(const std::string& title) { title_ = title; }
    void setXLabel(const std::string& label) { x_label_ = label; }
    void setYLabel(const std::string& label) { y_label_ = label; }

    const std::string& getTitle() const { return title_; }
    const std::string& getXLabel() const { return x_label_; }
    const std::string& getYLabel() const { return y_label_; }

    virtual std::string summary() const = 0;
    virtual std::string renderSVG(int width = 800, int height = 500) const = 0;
};

} // namespace dataviz

#endif // DATAVIZ_PLOT_HPP
