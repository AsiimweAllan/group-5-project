#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

struct Color {
    uint8_t r, g, b;
};

class CountPlot {
private:
    std::vector<std::string> data_;
    std::string x_label_;
    std::string y_label_ = "count";
    std::string title_;
    Color bar_color_ = {70, 130, 180}; // Steel Blue

public:
    explicit CountPlot(const std::vector<std::string>& data) : data_(data) {}

    void setXLabel(const std::string& label) { x_label_ = label; }
    void setTitle(const std::string& title) { title_ = title; }

    // 1. Calculate category frequency counts
    std::map<std::string, std::size_t> computeFrequencies() const {
        std::map<std::string, std::size_t> counts;
        for (const auto& item : data_) {
            counts[item]++;
        }
        return counts;
    }

    // 2. Export / Render (Example generating SVG string output)
    std::string renderSVG(int width = 600, int height = 400) const {
        auto counts = computeFrequencies();
        if (counts.empty()) return "";

        // Find max count to scale bar heights relative to SVG dimensions
        std::size_t max_count = 0;
        for (const auto& [category, count] : counts) {
            max_count = std::max(max_count, count);
        }

        std::string svg = "<svg width=\"" + std::to_string(width) + 
                          "\" height=\"" + std::to_string(height) + 
                          "\" xmlns=\"http://www.w3.org/2000/svg\">\n";

        int margin = 50;
        int chart_width = width - 2 * margin;
        int chart_height = height - 2 * margin;
        int num_categories = static_cast<int>(counts.size());
        int slot_width = chart_width / num_categories;
        int bar_width = slot_width * 0.6; // 60% bar width, 40% spacing

        int i = 0;
        for (const auto& [category, count] : counts) {
            int x = margin + i * slot_width + (slot_width - bar_width) / 2;
            int bar_h = (static_cast<double>(count) / max_count) * chart_height;
            int y = margin + (chart_height - bar_h);

            // Draw Bar
            svg += "  <rect x=\"" + std::to_string(x) + 
                   "\" y=\"" + std::to_string(y) + 
                   "\" width=\"" + std::to_string(bar_width) + 
                   "\" height=\"" + std::to_string(bar_h) + 
                   "\" fill=\"rgb(" + std::to_string(bar_color_.r) + "," 
                                   + std::to_string(bar_color_.g) + "," 
                                   + std::to_string(bar_color_.b) + ")\"/>\n";

            // Draw Category Label below bar
            svg += "  <text x=\"" + std::to_string(x + bar_width / 2) + 
                   "\" y=\"" + std::to_string(height - margin / 2) + 
                   "\" text-anchor=\"middle\" font-size=\"12\">" + category + "</text>\n";

            i++;
        }

        svg += "</svg>";
        return svg;
    }