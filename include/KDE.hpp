#ifndef KDE_HPP
#define KDE_HPP

#include <vector>
#include<utility>
// KDE = Kernel Density Estimation
// This class shows where our data is concentrated mostly in a given set of numerical values.

class KDE {
private:
    std::vector<double> data; // stores input data points
    double bandwidth; // controls the smoothness of the final KDE curve.

public:
    KDE(const std::vector<double>& data, double bandwidth);
    // receives the dataset to be analyzed and the bandwidth used for the KDE calc.
    double evaluate(double x) const;
    // calculates the KDE density at a specific point x value.
    // eg : kde.evaluate(50)
    std::vector<std::pair<double, double>> evaluateRange(
    double start,
    double end,
    double step
) const;

};
#endif
