
#ifndef DATAVIZ_AXIS_HPP
#define DATAVIZ_AXIS_HPP

#include <string>
#include <vector>

class AxisData {
private:
    double minValue;
    double maxValue;
    std::string axisLabel;
    std::vector<double> ticks;
    std::vector<std::string> labels;

public:
    AxisData();
    virtual ~AxisData() = default; // NEW

    void setRange(double min, double max);
    void setAxisLabel(const std::string& label);
    void setTicks(const std::vector<double>& values);
    void setLabels(const std::vector<std::string>& values);

    double getMinValue() const;
    double getMaxValue() const;
    std::string getAxisLabel() const;

    const std::vector<double>& getTicks() const;
    const std::vector<std::string>& getLabels() const;

    virtual void printDetails() const; // NEW: polymorphism
};

// NEW: inheritance
class LabeledAxis : public AxisData {
private:
    std::string unit;

public:
    LabeledAxis(const std::string& axisUnit);
    void printDetails() const override;
};

//prints the axis details to the terminal
void printAxis(const AxisData& axis);
double scaleValue(const AxisData& axis, double value);

#endif
