
#include <cmath>
#include <iostream>
#include "KDE.hpp"
#include<vector>
#include <utility>

int main()
{
    KDE kde({0.0}, 1.0);

    double result = kde.evaluate(0.0);

    double expected = 1.0 / std::sqrt(
        2.0 * 3.14159265358979323846
    );

    double difference = std::abs(result - expected);

    std::cout << "Calculated: " << result << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "Difference: " << difference << '\n';
    std::cout << "Tolerance: " << 1e-6 << '\n';

    if (difference < 1e-6)
    {
        std::cout << "Test passed!\n";
    }
    else
    {
        std::cout << "Test failed!\n";
    }

    // Test evaluating KDE across a range.
    KDE rangeKde({2.0, 3.0, 4.0}, 1.0);

    // Calculate densities from x = 0 to x = 6 in steps of 1.
    std::vector<std::pair<double, double>> points =
        rangeKde.evaluateRange(0.0, 6.0, 1.0);

    // We expect seven coordinate pairs: 0, 1, 2, 3, 4, 5, 6.
    if (points.size() == 7)
    {
        std::cout << "Range test passed!\n";
    }
    else
    {
        std::cout << "Range test failed!\n";
    }

    // Display the calculated coordinate pairs.
    for (const auto& point : points)
    {
        std::cout << "x = " << point.first
                  << ", density = " << point.second << '\n';
    }

    return 0;
}

