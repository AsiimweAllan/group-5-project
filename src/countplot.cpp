
#include "countplot.hpp"
#include "axis.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace dataviz {

namespace {

std::string escapeXML(const std::string& text) {
    std::string result;

    for (char ch : text) {
        switch (ch) {
            case '&': result += "&amp;"; break;
            case '<': result += "&lt;"; break;
            case '>': result += "&gt;"; break;
            case '"': result += "&quot;"; break;
            case '\'': result += "&apos;"; break;
            default: result += ch; break;
        }
    }

    return result;
}

std::string formatNumber(
    double value,
    int precision = 0
) {
    std::ostringstream out;

    out << std::fixed
        << std::setprecision(precision)
        << value;

    return out.str();
}

}

void Plot::setXLabel(const std::string& label) {
    x_label_ = label;
}

void Plot::setYLabel(const std::string& label) {
    y_label_ = label;
}

void Plot::setTitle(const std::string& title) {
    title_ = title;
}

CountPlot::CountPlot(
    const std::vector<std::string>& categories
) : categories_(categories) {
}

void CountPlot::setBarColor(Color color) {
    bar_color_ = color;
}

std::map<std::string, std::size_t>
CountPlot::counts() const {
    std::map<std::string, std::size_t> categoryCounts;

    for (const auto& category : categories_) {
        ++categoryCounts[category];
    }

    return categoryCounts;
}

std::map<std::string, std::size_t>
CountPlot::computeFrequencies() const {
    return counts();
}

std::string CountPlot::summary() const {
    const auto categoryCounts = counts();

    std::string message = title_ + " counts:";

    if (categoryCounts.empty()) {
        return message + " No categories available.";
    }

    for (const auto& item : categoryCounts) {
        message += " " + item.first + " = "
                + std::to_string(item.second) + ";";
    }

    return message;
}

std::string CountPlot::renderSVG(
    int width,
    int height
) const {
    if (width < 400 || height < 300) {
        throw std::invalid_argument(
            "SVG dimensions must be at least 400 x 300"
        );
    }

    const auto categoryCounts = computeFrequencies();

    if (categoryCounts.empty()) {
        throw std::invalid_argument(
            "Cannot generate a chart from empty data"
        );
    }

    if (categoryCounts.size() > 20) {
        throw std::invalid_argument(
            "Too many categories. Maximum supported is 20"
        );
    }

    const int left = 80;
    const int right = 35;
    const int top = 65;
    const int bottom = 100;

    const int chartWidth = width - left - right;
    const int chartHeight = height - top - bottom;

    const double slotWidth =
        static_cast<double>(chartWidth) /
        categoryCounts.size();

    const double barWidth =
        std::max(1.0, std::min(55.0, slotWidth * 0.6));

    std::size_t maxCount = 0;

    for (const auto& entry : categoryCounts) {
        maxCount = std::max(maxCount, entry.second);
    }

    const double axisMaximum =
        std::max(5.0, std::ceil(maxCount / 5.0) * 5.0);

    AxisData yAxis;

    yAxis.setRange(0.0, axisMaximum);
    yAxis.setAxisLabel(y_label_);

    std::vector<double> tickValues;
    std::vector<std::string> tickLabels;

    for (int tick = 0; tick <= 5; ++tick) {
        const double value = axisMaximum * tick / 5.0;

        tickValues.push_back(value);
        tickLabels.push_back(formatNumber(value));
    }

    yAxis.setTicks(tickValues);
    yAxis.setLabels(tickLabels);

    std::ostringstream svg;

    svg << "<svg xmlns=\"http://www.w3.org/2000/svg\" "
        << "width=\"" << width
        << "\" height=\"" << height
        << "\" viewBox=\"0 0 "
        << width << " " << height << "\">\n";

    svg << "<rect width=\"100%\" height=\"100%\" "
        << "fill=\"white\"/>\n";

    svg << "<g font-family=\"Arial, sans-serif\" "
        << "fill=\"#253044\">\n";

    svg << "<text x=\"" << width / 2
        << "\" y=\"30\" text-anchor=\"middle\" "
        << "font-size=\"20\" font-weight=\"bold\">"
        << escapeXML(title_)
        << "</text>\n";

    const auto& ticks = yAxis.getTicks();
    const auto& labels = yAxis.getLabels();

    for (std::size_t tick = 0; tick < ticks.size(); ++tick) {
        const double value = ticks[tick];

        const double y =
            top + chartHeight *
            (1.0 - scaleValue(yAxis, value));

        svg << "<line x1=\"" << left
            << "\" y1=\"" << y
            << "\" x2=\"" << width - right
            << "\" y2=\"" << y
            << "\" stroke=\"#e3e8ef\"/>\n";

        svg << "<text x=\"" << left - 10
            << "\" y=\"" << y + 4
            << "\" text-anchor=\"end\" "
            << "font-size=\"11\">"
            << escapeXML(labels[tick])
            << "</text>\n";
    }

    svg << "<line x1=\"" << left
        << "\" y1=\"" << top
        << "\" x2=\"" << left
        << "\" y2=\"" << top + chartHeight
        << "\" stroke=\"#536071\"/>\n";

    svg << "<line x1=\"" << left
        << "\" y1=\"" << top + chartHeight
        << "\" x2=\"" << width - right
        << "\" y2=\"" << top + chartHeight
        << "\" stroke=\"#536071\"/>\n";

    std::size_t index = 0;

    for (const auto& entry : categoryCounts) {
        const std::string& category = entry.first;
        const std::size_t count = entry.second;

        const double center =
            left + (index + 0.5) * slotWidth;

        const double barHeight =
            scaleValue(
                yAxis,
                static_cast<double>(count)
            ) * chartHeight;

        const double x = center - barWidth / 2.0;

        const double y =
            top + chartHeight - barHeight;

        svg << "<rect x=\"" << x
            << "\" y=\"" << y
            << "\" width=\"" << barWidth
            << "\" height=\"" << barHeight
            << "\" rx=\"3\" fill=\"rgb("
            << static_cast<int>(bar_color_.r) << ","
            << static_cast<int>(bar_color_.g) << ","
            << static_cast<int>(bar_color_.b)
            << ")\"/>\n";

        svg << "<text x=\"" << center
            << "\" y=\"" << std::max(50.0, y - 8.0)
            << "\" text-anchor=\"middle\" "
            << "font-size=\"12\" font-weight=\"bold\">"
            << count
            << "</text>\n";

        std::string label = category;

        if (label.size() > 14) {
            label = label.substr(0, 11) + "...";
        }

        svg << "<text x=\"" << center
            << "\" y=\"" << top + chartHeight + 20
            << "\" text-anchor=\"middle\" "
            << "font-size=\"11\">"
            << escapeXML(label)
            << "</text>\n";

        ++index;
    }

    svg << "<text x=\"" << width / 2
        << "\" y=\"" << height - 25
        << "\" text-anchor=\"middle\" "
        << "font-size=\"14\">"
        << escapeXML(x_label_)
        << "</text>\n";

    svg << "<text transform=\"translate(22 "
        << top + chartHeight / 2
        << ") rotate(-90)\" "
        << "text-anchor=\"middle\" font-size=\"14\">"
        << escapeXML(yAxis.getAxisLabel())
        << "</text>\n";

    svg << "</g>\n</svg>\n";

    return svg.str();
}

}
