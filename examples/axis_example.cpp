#include "axis.hpp"

int main() {
    // Create an AxisData variable
    AxisData Axis;

    // Assign basic settings
    Axis.minValue = 0;
    Axis.maxValue = 100;
    Axis.axisLabel = "Score";

    // Add numbers and labels
    Axis.ticks = {0, 20, 40, 60, 80, 100};
    Axis.labels = {"0", "20", "40", "60", "80", "100"};

    // Display everything on screen
    printAxis(Axis);

    return 0;
}