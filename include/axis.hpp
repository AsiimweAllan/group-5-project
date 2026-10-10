#ifndef DATAVIZ_AXIS_HPP
#define DATAVIZ_AXIS_HPP

#include <string>
#include <vector>

// Defining astructure to hold the axis data
struct AxisData {
    double minValue;
    double maxValue;
    std::string axisLabel;
    std::vector<double> ticks;
    std::vector<std::string> labels;
};

//prints the axis details to the terminal
void printAxis(const AxisData& axis);

#endif