#include "countplot.hpp"

#include <cassert>
#include <stdexcept>
#include <string>
#include <vector>

int main() {
    dataviz::CountPlot plot({"Apple", "Banana", "Apple", "A&B"});
    plot.setTitle("Fruit <counts>");
    plot.setXLabel("Fruit & type");
    plot.setYLabel("Number <of> items");

    const auto counts = plot.counts();
    assert(counts.size() == 3);
    assert(counts.at("Apple") == 2);
    assert(counts.at("Banana") == 1);
    assert(counts.at("A&B") == 1);
    assert(plot.computeFrequencies() == counts);

    const std::string summary = plot.summary();
    assert(summary.find("Fruit <counts> counts:") != std::string::npos);
    assert(summary.find("Apple = 2") != std::string::npos);

    const std::string svg = plot.renderSVG(400, 300);
    assert(svg.find("<svg") != std::string::npos);
    assert(svg.find("Fruit &lt;counts&gt;") != std::string::npos);
    assert(svg.find("A&amp;B") != std::string::npos);
    assert(svg.find("Fruit &amp; type") != std::string::npos);
    assert(svg.find("Number &lt;of&gt; items") != std::string::npos);
    assert(svg.find("width=\"400\" height=\"300\"") != std::string::npos);

    bool threw = false;
    try {
        (void)plot.renderSVG(399, 300);
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    assert(threw);

    const dataviz::CountPlot empty({});
    assert(empty.counts().empty());
    assert(empty.summary().find("No categories available") != std::string::npos);
    threw = false;
    try {
        (void)empty.renderSVG();
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    assert(threw);

    std::vector<std::string> tooManyCategories;
    for (int i = 0; i < 21; ++i) {
        tooManyCategories.push_back("Category" + std::to_string(i));
    }
    const dataviz::CountPlot tooMany(tooManyCategories);
    threw = false;
    try {
        (void)tooMany.renderSVG();
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    assert(threw);

    return 0;
}
