#include "axis.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    AxisData axis;
    assert(axis.getMinValue() == 0.0);
    assert(axis.getMaxValue() == 100.0);
    assert(axis.getAxisLabel().empty());

    axis.setRange(0.0, 100.0);
    axis.setAxisLabel("Score");
    axis.setTicks({0.0, 25.0, 50.0, 75.0, 100.0});
    axis.setLabels({"0", "25", "50", "75", "100"});

    assert(axis.getMinValue() == 0.0);
    assert(axis.getMaxValue() == 100.0);
    assert(axis.getAxisLabel() == "Score");
    assert(axis.getTicks() == std::vector<double>({0.0, 25.0, 50.0, 75.0, 100.0}));
    assert(axis.getLabels() == std::vector<std::string>({"0", "25", "50", "75", "100"}));

    // Invalid ranges are ignored, leaving the last valid range unchanged.
    axis.setRange(100.0, 0.0);
    assert(axis.getMinValue() == 0.0);
    assert(axis.getMaxValue() == 100.0);

    assert(scaleValue(axis, 0.0) == 0.0);
    assert(scaleValue(axis, 50.0) == 0.5);
    assert(scaleValue(axis, 100.0) == 1.0);
    assert(scaleValue(axis, 150.0) == 1.5);

    std::ostringstream captured;
    auto* oldBuffer = std::cout.rdbuf(captured.rdbuf());
    printAxis(axis);
    std::cout.rdbuf(oldBuffer);
    assert(captured.str().find("Axis Name: Score") != std::string::npos);
    assert(captured.str().find("Range: 0 to 100") != std::string::npos);

    // Show the values when running the test executable directly.
    printAxis(axis);
    std::cout << "Scaled value at 50: " << scaleValue(axis, 50.0) << '\n';
    std::cout << "Axis test passed.\n";
    return 0;
}
