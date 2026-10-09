#include "KDE.hpp"
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

std::vector<std::pair<double, double>> KDE::evaluateRange(
    double start,
    double end,
    double step
) const
{
    // Store all the (x, density) coordinate pairs here.
    std::vector<std::pair<double, double>> results;

    // The step must be positive.
    if (step <= 0)
    {
        throw std::invalid_argument("Step must be greater than 0.");
    }

    // The ending x-value cannot be less than the starting x-value.
    if (end < start)
    {
        throw std::invalid_argument("End must be greater than or equal to start.");
    }

    // A loop to start at the first x-value and move across the range.
    
    // Calculate the number of intervals in the requested range.
    double intervalCount = (end - start) / step;

    // Generate each x-value using its index.
    for (int i = 0; i <= intervalCount; ++i)
    {
        double x = start + i * step;

        // Calculate the density at this x-value.
        double density = evaluate(x);

        // Store the coordinate pair.
        results.push_back({x, density});
    }

    return results;
}
