#include "countplot.hpp"

#include <algorithm>
#include <iomanip>
#include <sstream>

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

size_t CountPlot::total() const {
    return categories_.size();
}

vector<pair<string, size_t>> CountPlot::sortedCounts() const {
    map<string, size_t> categoryCounts = counts();
    vector<pair<string, size_t>> sorted(categoryCounts.begin(), categoryCounts.end());

    // stable_sort keeps alphabetical order for categories with equal counts.
    stable_sort(sorted.begin(), sorted.end(),
                [](const pair<string, size_t>& a, const pair<string, size_t>& b) {
                    return a.second > b.second;
                });

    return sorted;
}

string CountPlot::mostCommon() const {
    vector<pair<string, size_t>> sorted = sortedCounts();

    if (sorted.empty()) {
        return "";
    }

    return sorted.front().first;
}

map<string, double> CountPlot::percentages() const {
    map<string, double> result;
    size_t totalItems = total();

    // With no data there is nothing to divide, so return an empty map.
    if (totalItems == 0) {
        return result;
    }

    for (const auto& item : counts()) {
        result[item.first] = 100.0 * item.second / totalItems;
    }

    return result;
}

string CountPlot::textChart(size_t maxWidth) const {
    vector<pair<string, size_t>> sorted = sortedCounts();

    if (sorted.empty()) {
        return title_ + ": no data\n";
    }

    // Find the longest label so the bars line up.
    size_t labelWidth = 0;
    for (const auto& item : sorted) {
        labelWidth = max(labelWidth, item.first.size());
    }

    size_t highest = sorted.front().second;
    ostringstream out;
    out << title_ << "\n";

    for (const auto& item : sorted) {
        // Scale the bar to maxWidth, but always show at least one block.
        size_t barLength = max<size_t>(1, item.second * maxWidth / highest);
        out << left << setw(static_cast<int>(labelWidth)) << item.first << " | "
            << string(barLength, '#') << " " << item.second << "\n";
    }

    return out.str();
}

}