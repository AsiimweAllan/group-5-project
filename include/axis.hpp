
#ifndef DATAVIZ_AXIS_HPP
#define DATAVIZ_AXIS_HPP

#include <string>
#include <vector>

// Base class representing an axis in a data visualization
class AxisData {
private:
    // Private data members: encapsulation
    double minValue;
    double maxValue;
    std::string axisLabel;
    std::vector<double> ticks;
    std::vector<std::string> labels;

public:
    // Constructor and virtual destructor
    AxisData();
    virtual ~AxisData() = default;

    // Setter functions
    void setRange(double min, double max);
    void setAxisLabel(const std::string& label);
    void setTicks(const std::vector<double>& values);
    void setLabels(const std::vector<std::string>& values);

    // Getter functions
    double getMinValue() const;
    double getMaxValue() const;
    std::string getAxisLabel() const;

    const std::vector<double>& getTicks() const;
    const std::vector<std::string>& getLabels() const;

    // Virtual function: supports runtime polymorphism
    virtual void printDetails() const;
};


// Derived class demonstrating inheritance
class LabeledAxis : public AxisData {
private:
    std::string unit;

public:
    // Constructor accepts the measurement unit
    explicit LabeledAxis(const std::string& axisUnit);

    // Overrides the base class implementation
    void printDetails() const override;
};


// Standalone utility functions
void printAxis(const AxisData& axis);
double scaleValue(const AxisData& axis, double value);

#endif // DATAVIZ_AXIS_HPP
