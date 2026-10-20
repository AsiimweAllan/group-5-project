
#include "axis.hpp"
#include <iostream>

using namespace std;

int main() {
    // Original axis
    AxisData axis;
    axis.setAxisLabel("Score");
    axis.setRange(0, 100);
    axis.setTicks({0, 20, 40, 60, 80, 100});
    axis.setLabels({"0", "20", "40", "60", "80", "100"});

    printAxis(axis);
    cout << "A score of 50 scales to "
         << scaleValue(axis, 50) << endl;

    cout << endl;

    // New inherited axis
    LabeledAxis temperatureAxis("Degrees Celsius");
    temperatureAxis.setAxisLabel("Temperature");
    temperatureAxis.setRange(0, 100);
    temperatureAxis.setLabels({"0", "20", "40", "60", "80", "100"});

    // Demonstrates polymorphism
    printAxis(temperatureAxis);

    return 0;
}
