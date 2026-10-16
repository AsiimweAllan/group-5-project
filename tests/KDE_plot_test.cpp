#include "KDE.h"

#include <cassert>
#include <cmath>
#include <stdexcept>
#include <vector>
using namespace std;
namespace {

constexpr double kKernelPi = 3.14159;

void expect_close(double actual, double expected, double tolerance) {
    assert(fabs(actual - expected) <= tolerance);
}

}  // namespace

int main() {
    // Constructor should reject empty data.
    bool threw = false;
    try {
        KDE empty_data({}, 1.0);
    } catch (const invalid_argument&) {
        threw = true;
    }
    assert(threw);

    // Constructor should reject non-positive bandwidth.
    threw = false;
    try {
        KDE invalid_bandwidth({0.0, 1.0}, 0.0);
    } catch (const invalid_argument&) {
        threw = true;
    }
    assert(threw);

    // For a single point, the Gaussian KDE should peak at that point.
    const vector<double> single_point_data{0.0};
    const KDE single_point(single_point_data, 1.0);
    const double expected_peak = 1.0 / sqrt(2.0 * kKernelPi);
    expect_close(single_point.evaluate(0.0), expected_peak, 1e-12);

    // Density should be higher near the sample mean than far away.
    const vector<double> data{0.0, 10.0};
    const KDE kde(data, 1.0);
    assert(kde.evaluate(0.0) > kde.evaluate(20.0));
    assert(kde.evaluate(10.0) > kde.evaluate(-10.0));
    assert(isfinite(kde.evaluate(5.0)));

    return 0;
}
