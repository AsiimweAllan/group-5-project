#ifndef DATAVIZ_PLOT_HPP
#define DATAVIZ_PLOT_HPP

#include <string>

namespace dataviz {

// Parent class for plots that can describe their results.
class Plot {
protected:
    // Subclasses can use the title, but the rest of the program cannot edit it directly.
    std::string title_;

public:
    explicit Plot(const std::string& title) : title_(title) {}

    void setTitle(const std::string& title) {
        title_ = title;
    }

    std::string getTitle() const {
        return title_;
    }

    // Each child class must decide how it describes its own results.
    virtual std::string summary() const = 0;

    // A base class used polymorphically needs a virtual destructor.
    virtual ~Plot() = default;
};

}

#endif
