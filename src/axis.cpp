#include "axis.hpp"
#include <iostream>

AxisData::AxisData()
    : minValue(0), maxValue(100), axisLabel("") {
}

void AxisData::setRange(double min, double max) {
    if (min < max) {
        minValue = min;
        maxValue = max;
    }
}

void AxisData::setAxisLabel(const std::string& label) {
    axisLabel = label;
}

void AxisData::setTicks(const std::vector<double>& values) {
    ticks = values;
}

void AxisData::setLabels(
    const std::vector<std::string>& values) {
    labels = values;
}

double AxisData::getMinValue() const {
    return minValue;
}

double AxisData::getMaxValue() const {
    return maxValue;
}

std::string AxisData::getAxisLabel() const {
    return axisLabel;
}

const std::vector<double>& AxisData::getTicks() const {
    return ticks;
}

const std::vector<std::string>& AxisData::getLabels() const {
    return labels;
}

void printAxis(const AxisData& axis) {
    std::cout << "Axis Name: "
              << axis.getAxisLabel() << std::endl;

    std::cout << "Range: "
              << axis.getMinValue() << " to "
              << axis.getMaxValue() << std::endl;

    std::cout << "Labels: ";

    for (const std::string& label : axis.getLabels()) {
        std::cout << label << " ";
    }

    std::cout << std::endl;
}

double scaleValue(const AxisData& axis, double value) {
    if (axis.getMaxValue() == axis.getMinValue()) {
        return 0.0;
    }

    return (value - axis.getMinValue()) /
           (axis.getMaxValue() - axis.getMinValue());
}