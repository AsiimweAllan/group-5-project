#include "histogram.hpp"

#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    const dataviz::TextHistogram histogram({2, 3, 3, 4, 4, 4, -1});
    const std::map<int, std::size_t> expected{
        {-1, 1}, {2, 1}, {3, 2}, {4, 3}
    };

    assert(histogram.counts() == expected);
    const std::string rendered = histogram.renderText();
    assert(rendered.find("HISTOGRAM") != std::string::npos);
    assert(rendered.find("-1: *") != std::string::npos);
    assert(rendered.find("3: **") != std::string::npos);
    assert(rendered.find("4: ***") != std::string::npos);

    const dataviz::TextHistogram empty({});
    assert(empty.counts().empty());
    assert(empty.renderText() == "HISTOGRAM\n---------\n");

    std::cout << "Histogram behavior passed.\n";
    return 0;
}
