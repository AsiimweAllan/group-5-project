
#include "axis.hpp"
#include <iostream>

using namespace std;

int main() {
    // 1. Demonstrate the original AxisData class
    AxisData axis;

    axis.setAxisLabel("Score");
    axis.setRange(0, 100);
    axis.setTicks({0, 20, 40, 60, 80, 100});
    axis.setLabels({"0", "20", "40", "60", "80", "100"});

    cout << " STANDARD AXIS " << endl;
    printAxis(axis);

    cout << "A score of 50 scales to: "
         << scaleValue(axis, 50) << endl;

    // 2. Demonstrate inheritance and polymorphism
   
    LabeledAxis temperatureAxis("Degrees Celsius");

    temperatureAxis.setAxisLabel("Temperature");
    temperatureAxis.setRange(0, 100);
    temperatureAxis.setTicks({0, 20, 40, 60, 80, 100});
    temperatureAxis.setLabels({"0", "20", "40", "60", "80", "100"});

    cout << "\n========== LABELED AXIS ==========" << endl;

    // Calls the overridden printDetails() function
    printAxis(temperatureAxis);

    cout << "\nProgram completed successfully." << endl;

    return 0;
}
