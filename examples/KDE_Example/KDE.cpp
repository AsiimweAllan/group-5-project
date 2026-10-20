
#include "KDE.h"
#include <cmath>
#include <stdexcept>

// the constructor receives data and bandwidith and keeps them in the object's private variables
KDE::KDE(const std::vector<double>& data, double bandwidth)// a constructor will initialise an object when it is created
    : data(data), bandwidth(bandwidth)
{
    if (data.empty() || bandwidth <= 0) {// the constructor will also check if the data is empty or bandwidith is positive
        throw std::invalid_argument(
            "Data must not be empty and bandwidth must be positive."
        );
    }
}

double KDE::evaluate(double x) const
{
    const double pi = 3.14159265358979323846;
    double sum = 0.0;

    for (double value : data) {
        double z = (x - value) / bandwidth;
        sum += std::exp(-0.5 * z * z);
    }

    return sum / (data.size() * bandwidth *
                  std::sqrt(2.0 * pi));
}
