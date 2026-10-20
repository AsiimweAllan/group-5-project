
#ifndef KDE_H
#define KDE_H

#include <vector>

// KDE = Kernel Density Estimation
// Shows where data is concentrated.

class KDE {
private:
    std::vector<double> data;
    double bandwidth;

public:
    KDE(const std::vector<double>& data, double bandwidth);

    double evaluate(double x) const;
};

#endif
