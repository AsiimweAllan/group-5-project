#ifndef SURVEY_COUNTPLOT_HPP
#define SURVEY_COUNTPLOT_HPP

#include <cstddef>
#include <map>
#include <string>
#include <vector>

namespace survey {

// parent class representing a general settings
class Plot {
protected: // here we use protected not private because it allows the child class to access this, rather than private that wouldnt accept the child class to access this
    std::string title_;

public: // declare public members
    explicit Plot(const std::string& title)
        : title_(title) {}

    virtual ~Plot() = default;

    // Pure virtual function is the parent class telling the child class to customize its own version
    virtual std::string summary() const = 0;
};

// Derived class whose custom job is to take data, the assesment preferences, and runthe for loop to see the frequent repetition. more like tallying usinf the std::map
class CountPlot : public Plot {
private:
    std::vector<std::string> categories_;

public:
    explicit CountPlot(std::vector<std::string> categories);

    // Core logic to tally frequenciesz
    std::map<std::string, std::size_t> counts() const;

    // Override summary to display category counts
    std::string summary() const override;
};

} 

#endif 