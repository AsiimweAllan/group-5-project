#include "KDE.hpp"
#include "axis.hpp"
#include "countplot.hpp"
#include "data_loader.hpp"
#include "histogram.hpp"

#include <iostream>
#include <vector>

int main() {
    dataviz::AxisData axis;
    axis.setAxisLabel("Score");
    axis.setRange(0.0, 100.0);
    std::cout << "Scaled score 50: " << dataviz::scaleValue(axis, 50.0) << '\n';

    dataviz::KDE density({60.0, 70.0, 80.0, 90.0}, 5.0);
    std::cout << "Estimated density at 75: " << density.evaluate(75.0) << '\n';

    dataviz::TextHistogram histogram({2, 3, 3, 4, 4, 4, 5, 5});
    std::cout << histogram.renderText();

    dataviz::CountPlot counts({"A", "B", "A", "C", "B", "A"});
    std::cout << counts.summary() << '\n';
    return 0;
}
