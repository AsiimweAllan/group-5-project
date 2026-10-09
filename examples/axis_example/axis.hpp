#ifndef AXIS_HPP
#define AXIS_HPP

#include <string>
#include <vector>

struct AxisData {
    std::string axisLabel;
    double minValue;
    double maxValue;
    std::vector<std::string> labels;
};

void printAxis(const AxisData& axis);

#endif