#include "axis.hpp"
#include <iostream>

// Implementation of the print function
void printAxis(const AxisData& axis) {
    // Print the name of the axis
    std::cout << "Axis Name: " << axis.axisLabel << std::endl;
    
    // Print range info
    std::cout << "Range: " << axis.minValue << " to " << axis.maxValue << std::endl;
    
    // Print each tick label
    std::cout << "Labels: ";
    for (size_t i = 0; i < axis.labels.size(); i++) {
        std::cout << axis.labels[i] << " ";
    }
    std::cout << std::endl;
}