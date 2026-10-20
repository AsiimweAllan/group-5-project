
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

struct Color {
    std::uint8_t r, g, b;
};

std::string escapeXML(const std::string& text) {
    std::string result;
    for (char ch : text) {
        switch (ch) {
            case '&': result += "&amp;"; break;
            case '<': result += "&lt;"; break;
            case '>': result += "&gt;"; break;
            case '"': result += "&quot;"; break;
            case '\'': result += "&apos;"; break;
            default: result += ch;
        }
    }
    return result;
}

class Plot {
protected:
    std::string x_label_;
    std::string y_label_;
    std::string title_;

public:
    virtual ~Plot() = default;

    void setXLabel(const std::string& label) {
        x_label_ = label;
    }

    void setYLabel(const std::string& label) {
        y_label_ = label;
    }

    void setTitle(const std::string& title) {
        title_ = title;
    }

    virtual std::string renderSVG(
        int width = 600,
        int height = 400
    ) const = 0;
};

class CountPlot : public Plot {
private:
    std::vector<std::string> data_;
    Color bar_color_ = {70, 130, 180};

public:
    explicit CountPlot(const std::vector<std::string>& data)
        : data_(data) {
        y_label_ = "Count";
    }

    std::map<std::string, std::size_t> computeFrequencies() const {
        std::map<std::string, std::size_t> counts;

        for (const auto& item : data_) {
            ++counts[item];
        }

        return counts;
    }

    std::string renderSVG(
        int width = 600,
        int height = 400
    ) const override {
        const auto counts = computeFrequencies();

        if (counts.empty()) return "";

        if (width < 200 || height < 200)
            throw std::invalid_argument(
                "SVG dimensions must be at least 200"
            );

        const int margin = 65;
        const int chartWidth = width - 2 * margin;
        const int chartHeight = height - 2 * margin;
        const int slotWidth =
            chartWidth / static_cast<int>(counts.size());

        if (slotWidth < 1)
            throw std::invalid_argument(
                "Too many categories for the SVG width"
            );

        const int barWidth = std::max(1, slotWidth * 3 / 5);

        std::size_t maxCount = 0;

        for (const auto& entry : counts) {
            maxCount = std::max(maxCount, entry.second);
        }

        std::string svg =
            "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" +
            std::to_string(width) + "\" height=\"" +
            std::to_string(height) + "\">\n";

        svg += "<text x=\"" + std::to_string(width / 2) +
               "\" y=\"24\" text-anchor=\"middle\">" +
               escapeXML(title_) + "</text>\n";

        svg += "<text x=\"" + std::to_string(width / 2) +
               "\" y=\"" + std::to_string(height - 8) +
               "\" text-anchor=\"middle\">" +
               escapeXML(x_label_) + "</text>\n";

        svg += "<text x=\"8\" y=\"" +
               std::to_string(margin - 10) + "\">" +
               escapeXML(y_label_) + "</text>\n";

        int i = 0;

        for (const auto& [category, count] : counts) {
            const int x =
                margin + i * slotWidth +
                (slotWidth - barWidth) / 2;

            const int barHeight =
                static_cast<int>(
                    static_cast<double>(count) /
                    maxCount * chartHeight
                );

            const int y = margin + chartHeight - barHeight;

            svg += "<rect x=\"" + std::to_string(x) +
                   "\" y=\"" + std::to_string(y) +
                   "\" width=\"" + std::to_string(barWidth) +
                   "\" height=\"" + std::to_string(barHeight) +
                   "\" fill=\"rgb(" +
                   std::to_string(bar_color_.r) + "," +
                   std::to_string(bar_color_.g) + "," +
                   std::to_string(bar_color_.b) +
                   ")\"/>\n";

            svg += "<text x=\"" +
                   std::to_string(x + barWidth / 2) +
                   "\" y=\"" +
                   std::to_string(height - margin + 18) +
                   "\" font-size=\"12\" text-anchor=\"middle\">" +
                   escapeXML(category) + "</text>\n";

            ++i;
        }

        return svg + "</svg>\n";
    }
};

class PercentagePlot : public Plot {
private:
    std::vector<std::string> data_;
    Color bar_color_ = {46, 139, 87};

public:
    explicit PercentagePlot(
        const std::vector<std::string>& data
    ) : data_(data) {
        y_label_ = "Percentage (%)";
    }

    std::map<std::string, double> computePercentages() const {
        std::map<std::string, double> percentages;

        if (data_.empty()) return percentages;

        for (const auto& item : data_) {
            ++percentages[item];
        }

        for (auto& entry : percentages) {
            entry.second =
                entry.second * 100.0 / data_.size();
        }

        return percentages;
    }

    std::string renderSVG(
        int width = 600,
        int height = 400
    ) const override {
        const auto percentages = computePercentages();

        if (percentages.empty()) return "";

        if (width < 200 || height < 200)
            throw std::invalid_argument(
                "SVG dimensions must be at least 200"
            );

        const int margin = 65;
        const int chartWidth = width - 2 * margin;
        const int chartHeight = height - 2 * margin;

        const int slotWidth =
            chartWidth / static_cast<int>(percentages.size());

        if (slotWidth < 1)
            throw std::invalid_argument(
                "Too many categories for the SVG width"
            );

        const int barWidth = std::max(1, slotWidth * 3 / 5);

        std::string svg =
            "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" +
            std::to_string(width) + "\" height=\"" +
            std::to_string(height) + "\">\n";

        svg += "<text x=\"" + std::to_string(width / 2) +
               "\" y=\"24\" text-anchor=\"middle\">" +
               escapeXML(title_) + "</text>\n";

        svg += "<text x=\"" + std::to_string(width / 2) +
               "\" y=\"" + std::to_string(height - 8) +
               "\" text-anchor=\"middle\">" +
               escapeXML(x_label_) + "</text>\n";

        svg += "<text x=\"8\" y=\"" +
               std::to_string(margin - 10) + "\">" +
               escapeXML(y_label_) + "</text>\n";

        int i = 0;

        for (const auto& [category, percentage] : percentages) {
            const int x =
                margin + i * slotWidth +
                (slotWidth - barWidth) / 2;

            const int barHeight =
                static_cast<int>(
                    percentage / 100.0 * chartHeight
                );

            const int y = margin + chartHeight - barHeight;

            svg += "<rect x=\"" + std::to_string(x) +
                   "\" y=\"" + std::to_string(y) +
                   "\" width=\"" + std::to_string(barWidth) +
                   "\" height=\"" + std::to_string(barHeight) +
                   "\" fill=\"rgb(" +
                   std::to_string(bar_color_.r) + "," +
                   std::to_string(bar_color_.g) + "," +
                   std::to_string(bar_color_.b) +
                   ")\"/>\n";

            svg += "<text x=\"" +
                   std::to_string(x + barWidth / 2) +
                   "\" y=\"" +
                   std::to_string(height - margin + 18) +
                   "\" font-size=\"12\" text-anchor=\"middle\">" +
                   escapeXML(category) + "</text>\n";

            ++i;
        }

        return svg + "</svg>\n";
    }
};

int main() {
    const std::vector<std::string> categories = {
        "Apple", "Banana", "Apple",
        "Orange", "Banana", "Apple"
    };

    std::vector<std::unique_ptr<Plot>> plots;

    plots.push_back(
        std::make_unique<CountPlot>(categories)
    );

    plots.push_back(
        std::make_unique<PercentagePlot>(categories)
    );

    const std::vector<std::string> filenames = {
        "count_plot.svg",
        "percentage_plot.svg"
    };

    for (std::size_t i = 0; i < plots.size(); ++i) {
        plots[i]->setXLabel("Fruit category");

        plots[i]->setTitle(
            i == 0 ? "Fruit counts" : "Fruit percentages"
        );

        std::ofstream output(filenames[i]);

        if (!output) {
            std::cerr << "Could not open "
                      << filenames[i] << '\n';
            return 1;
        }

        output << plots[i]->renderSVG();

        std::cout << "Saved " << filenames[i] << '\n';
    }

    return 0;
}
