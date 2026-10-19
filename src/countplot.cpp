#include "countplot.hpp"

using namespace std;

namespace dataviz {

CountPlot::CountPlot(vector<string> categories)
    : Plot("Count plot") {
    categories_ = categories;
}

map<string, size_t> CountPlot::counts() const {
    map<string, size_t> categoryCounts;

    // Go through the list and add one to each category's count.
    for (const string& category : categories_) {
        categoryCounts[category]++;
    }

    return categoryCounts;
}

string CountPlot::summary() const {
    map<string, size_t> categoryCounts = counts();
    string message = title_ + " counts:";

    for (const auto& item : categoryCounts) {
        message = message + " " + item.first + " = " + to_string(item.second) + ";";
    }

    return message;
}

}