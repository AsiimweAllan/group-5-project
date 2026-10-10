#include "KDE.h"
#include <cmath>
#include <stdexcept> // works on invalid inputs like 0.
constexpr double PI = 3.14159;

// our constructor
KDE::KDE(const std::vector<double>& data, double bandwidth) : data(data), bandwidth(bandwidth){

    if(data.empty()){
        throw std::invalid_argument("KDE data cannot be empty.");
    } // KDE requires at least one data point.

    if(bandwidth <= 0){
        throw std::invalid_argument("KDE bandwidth must be a positive value.");
    } // bandwidth must be > 0.
    
}
// calculate KDE density at a specific x value.
double KDE::evaluate(double x) const {
    double sum = 0.0; 
// calculate the contribution of each data point.
    for (double xi : data) {
        double u = (x - xi) / bandwidth;
        sum += std::exp(-0.5 * u * u) / (std::sqrt(2.0 * PI)); // Gaussian kernel function.
    }
    return sum / (data.size() * bandwidth); // apply the KDE normalization factor 1/ (n * h).
}
