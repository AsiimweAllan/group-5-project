#include "axis.hpp"
#include <iostream>

int main() {
    AxisData Axis;

    Axis.setRange(0, 100);
    Axis.setAxisLabel("Score");

    Axis.setTicks({0, 20, 40, 60, 80, 100});
    Axis.setLabels({"0", "20", "40", "60", "80", "100"});

    printAxis(Axis);

    double value = 50;

    std::cout << "Value: " << value << std::endl;

    std::cout << "Scaled position: "
              << scaleValue(Axis, value)
              << std::endl;

    return 0;
}