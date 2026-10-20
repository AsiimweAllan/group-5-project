#ifndef DATAVIZ_PLOT_HPP
#define DATAVIZ_PLOT_HPP

#include <string>

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

}

#endif
