#include "axis.hpp"
#include <iostream>

using namespace dataviz;

int main() {
    AxisData axis;

    axis.setRange(0, 100);
    axis.setAxisLabel("Score");
    axis.setTicks({0, 20, 40, 60, 80, 100});
    axis.setLabels({"0", "20", "40", "60", "80", "100"});

    printAxis(axis);
    std::cout << "A score of 50 scales to: " << scaleValue(axis, 50) << '\n';

    return 0;
}
