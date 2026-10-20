
#include "axis.hpp"
#include <iostream>

using namespace std;

AxisData::AxisData()
    : minValue(0), maxValue(100), axisLabel("") {
}

void AxisData::setRange(double min, double max) {
    if (min < max) {
        minValue = min;
        maxValue = max;
    }
}

void AxisData::setAxisLabel(const string& label) {
    axisLabel = label;
}

void AxisData::setTicks(const vector<double>& values) {
    ticks = values;
}

void AxisData::setLabels(const vector<string>& values) {
    labels = values;
}


double AxisData::getMinValue() const {
    return minValue;
}

double AxisData::getMaxValue() const {
    return maxValue;
}

string AxisData::getAxisLabel() const {
    return axisLabel;
}

const vector<double>& AxisData::getTicks() const {
    return ticks;
}

const vector<string>& AxisData::getLabels() const {
    return labels;
}


void AxisData::printDetails() const {
    cout << "Axis Name: " << getAxisLabel() << endl;

    cout << "Range: "
         << getMinValue() << " to "
         << getMaxValue() << endl;

    cout << "Labels: ";

    for (const string& label : getLabels()) {
        cout << label << " ";
    }

    cout << endl;
}


LabeledAxis::LabeledAxis(const string& axisUnit)
    : unit(axisUnit) {
}


void LabeledAxis::printDetails() const {
    // Print the normal axis information first
    AxisData::printDetails();


    cout << "Unit: " << unit << endl;
}


void printAxis(const AxisData& axis) {
    axis.printDetails();
}


double scaleValue(const AxisData& axis, double value) {
    if (axis.getMaxValue() == axis.getMinValue()) {
        return 0.0;
    }

    return (value - axis.getMinValue()) /
           (axis.getMaxValue() - axis.getMinValue());
}
