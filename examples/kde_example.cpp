#include <iostream>
#include <vector>
#include "KDE.hpp"

int main() {
    // Example dataset.
    std::vector<double> data = {40, 42, 45, 47, 50, 52, 55, 57, 60};
    KDE kde(data, 5.0); // Create a KDE object with the dataset and a bandwidth of 5.0
    // Evaluate the density at a few x-values.
    std::cout << "KDE at x = 40: " << kde.evaluate(40) << '\n';
    std::cout << "KDE at x = 50: " << kde.evaluate(50) << '\n';
    std::cout << "KDE at x = 60: " << kde.evaluate(60) << '\n';

    return 0;
}