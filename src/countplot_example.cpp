
#include "countplot.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> categories = {
        "Apple", "Banana", "Apple",
        "Orange", "Banana", "Apple"
    };

    dataviz::CountPlot plot(categories);

    plot.setTitle("Fruit Counts");
    plot.setXLabel("Fruit Category");
    plot.setYLabel("Frequency");
    plot.setBarColor({70, 130, 180});

    std::cout << plot.summary() << std::endl;

    std::ofstream output("count_plot.svg");

    if (!output) {
        std::cerr << "Could not create SVG file.\n";
        return 1;
    }

    output << plot.renderSVG();

    output.close();

    std::cout << "Chart saved as count_plot.svg\n";

    return 0;
}
