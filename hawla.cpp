#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

std::vector<double> cleanData(const std::vector<double>& raw) {
    std::vector<double> clean;
    for (double v : raw)
        if (v >= 0) clean.push_back(v);   // drop invalid values
    return clean;
}

int main() {
    std::vector<double> data = {12, 7, -1, 25, 9, 14};
    auto d = cleanData(data);
    if (d.empty()) return 0;

    double sum = std::accumulate(d.begin(), d.end(), 0.0);
    std::cout << "Count: " << d.size() << "\n"
              << "Average: " << sum / d.size() << "\n"
              << "Min: " << *std::min_element(d.begin(), d.end()) << "\n"
              << "Max: " << *std::max_element(d.begin(), d.end()) << "\n";
}