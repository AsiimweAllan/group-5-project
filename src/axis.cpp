
#include "axis.hpp"
#include <iostream>

using namespace std;



// 1. AxisData constructor
// Initializes the axis with a default range of 0–100

AxisData::AxisData()
    : minValue(0), maxValue(100), axisLabel("") {
}


// 2. Setter functions
// Modify the private data members

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

// 3. Getter functions
// Provide access to private data without exposing it


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


// 4. Base class printing function
// Displays the standard axis information

void AxisData::printDetails() const {
    cout << "Axis Name: " << getAxisLabel() << endl;

    cout << "Range: "
         << getMinValue() << " to "
         << getMaxValue() << endl;

    cout << "Ticks: ";
    for (double tick : getTicks()) {
        cout << tick << " ";
    }
    cout << endl;

    cout << "Labels: ";
    for (const string& label : getLabels()) {
        cout << label << " ";
    }
    cout << endl;
}


// 5. LabeledAxis constructor
// Initializes the measurement unit

LabeledAxis::LabeledAxis(const string& axisUnit)
    : unit(axisUnit) {
}

// 6. Derived class printing function
// Extends the base class output with the unit

void LabeledAxis::printDetails() const {
    AxisData::printDetails();
    cout << "Unit: " << unit << endl;
}

// 7. Utility function to print an axis
// Demonstrates runtime polymorphism

void printAxis(const AxisData& axis) {
    axis.printDetails();
}


// 8. Utility function to scale a value
// Normalizes a value to a range from 0 to 1


double scaleValue(const AxisData& axis, double value) {
    double min = axis.getMinValue();
    double max = axis.getMaxValue();

    // Prevent division by zero
    if (max == min) {
        return 0.0;
    }

    return (value - min) / (max - min);
}
