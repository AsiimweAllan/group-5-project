#include "axis.hpp"
#include <iostream>

using namespace std;

// Implementating the print function
void printAxis(const AxisData& axis) {
    cout << "Axis Name: " << axis.axisLabel << endl;

    cout << "Range: " << axis.minValue
         << " to " << axis.maxValue << endl;

    cout << "Labels: ";

    for (size_t i = 0; i < axis.labels.size(); i++) {
        cout << axis.labels[i] << " ";
    }

    cout << endl;
}

int main() {
    
    AxisData xAxis;

    xAxis.axisLabel = "Students' Marks";
    xAxis.minValue = 0;
    xAxis.maxValue = 100;

    xAxis.labels = {"0", "20", "40", "60", "80", "100"};

    // show the axis information
    printAxis(xAxis);

    return 0;
}