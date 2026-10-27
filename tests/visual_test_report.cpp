#include "axis.hpp"
#include "data_loader.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace {

bool axisChecks(AxisData& axis, double& midpoint) {
    axis.setRange(0.0, 100.0);
    axis.setAxisLabel("Score");
    axis.setTicks({0.0, 25.0, 50.0, 75.0, 100.0});
    axis.setLabels({"0", "25", "50", "75", "100"});
    midpoint = scaleValue(axis, 50.0);
    return axis.getMinValue() == 0.0 && axis.getMaxValue() == 100.0 &&
           axis.getAxisLabel() == "Score" && midpoint == 0.5 &&
           axis.getTicks().size() == 5 && axis.getLabels().size() == 5;
}

bool csvChecks(const std::vector<std::vector<std::string>>& rows) {
    return rows.size() == 5 && rows[0].size() == 3 &&
           rows[0][0] == "name" && rows[0][1] == "score" && rows[0][2] == "group" &&
           rows[1][0] == "Ada" && rows[1][1] == "91" && rows[4][0] == "Dina";
}

void writeSvgReport(const std::vector<std::vector<std::string>>& rows,
                    bool axisPassed, bool csvPassed, double midpoint) {
    std::filesystem::create_directories("test-results");
    std::ofstream svg("test-results/summary.svg");
    if (!svg) throw std::runtime_error("Cannot create test-results/summary.svg");
    const bool allPassed = axisPassed && csvPassed;
    svg << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"900\" height=\"620\" viewBox=\"0 0 900 620\">"
        << "<rect width=\"900\" height=\"620\" fill=\"#f2f5f9\"/>"
        << "<text x=\"50\" y=\"52\" font-family=\"sans-serif\" font-size=\"28\" font-weight=\"700\" fill=\"#172033\">C++ project test results</text>"
        << "<text x=\"50\" y=\"88\" font-family=\"sans-serif\" font-size=\"17\" font-weight=\"700\" fill=\""
        << (allPassed ? "#087443" : "#b42318") << "\">" << (allPassed ? "PASS" : "FAIL")
        << " — AxisData and CSV fixture checks</text>"
        << "<rect x=\"40\" y=\"112\" width=\"820\" height=\"150\" rx=\"14\" fill=\"white\" stroke=\"#dbe2ec\"/>"
        << "<text x=\"65\" y=\"148\" font-family=\"sans-serif\" font-size=\"19\" font-weight=\"700\" fill=\"#172033\">AxisData: 0–100 range</text>"
        << "<line x1=\"120\" y1=\"195\" x2=\"780\" y2=\"195\" stroke=\"#526078\" stroke-width=\"4\"/>";
    const int ticks[] = {0, 25, 50, 75, 100};
    for (int i = 0; i < 5; ++i) {
        const int x = 120 + i * 165;
        svg << "<line x1=\"" << x << "\" y1=\"184\" x2=\"" << x << "\" y2=\"208\" stroke=\"#526078\"/>"
            << "<text x=\"" << x << "\" y=\"232\" text-anchor=\"middle\" font-family=\"sans-serif\" font-size=\"15\" fill=\"#526078\">"
            << ticks[i] << "</text>";
    }
    svg << "<circle cx=\"" << 120 + midpoint * 660 << "\" cy=\"195\" r=\"11\" fill=\"#e76f51\"/>"
        << "<text x=\"510\" y=\"151\" font-family=\"sans-serif\" font-size=\"14\" fill=\"#526078\">scaleValue(50) = " << midpoint << ""
        << (axisPassed ? " ✓" : " ✗") << "</text>"
        << "<rect x=\"40\" y=\"280\" width=\"820\" height=\"300\" rx=\"14\" fill=\"white\" stroke=\"#dbe2ec\"/>"
        << "<text x=\"65\" y=\"318\" font-family=\"sans-serif\" font-size=\"19\" font-weight=\"700\" fill=\"#172033\">DataLoader: scores read from CSV</text>"
        << "<line x1=\"100\" y1=\"520\" x2=\"800\" y2=\"520\" stroke=\"#526078\"/>";
    const int barX[] = {180, 330, 480, 630};
    for (std::size_t i = 1; i < rows.size() && i <= 4; ++i) {
        if (rows[i].size() < 3) continue;
        const int score = std::stoi(rows[i][1]);
        const int barHeight = score * 2;
        svg << "<rect x=\"" << barX[i - 1] << "\" y=\"" << 520 - barHeight
            << "\" width=\"80\" height=\"" << barHeight << "\" rx=\"6\" fill=\"#4587c7\"/>"
            << "<text x=\"" << barX[i - 1] + 40 << "\" y=\"" << 505 - barHeight
            << "\" text-anchor=\"middle\" font-family=\"sans-serif\" font-size=\"15\" fill=\"#172033\">" << score << "</text>"
            << "<text x=\"" << barX[i - 1] + 40 << "\" y=\"548\" text-anchor=\"middle\" font-family=\"sans-serif\" font-size=\"15\" fill=\"#526078\">"
            << rows[i][0] << "</text>";
    }
    svg << "<text x=\"65\" y=\"568\" font-family=\"sans-serif\" font-size=\"13\" fill=\"#65738a\">"
        << "CSV fixture check: " << (csvPassed ? "PASS" : "FAIL") << " · scores shown for Ada, Ben, Chen, and Dina</text>"
        << "</svg>\n";
}

void writeReport(const std::vector<std::vector<std::string>>& rows,
                 bool axisPassed, bool csvPassed, double midpoint) {
    std::filesystem::create_directories("test-results");
    std::ofstream html("test-results/index.html");
    if (!html) throw std::runtime_error("Cannot create test-results/index.html");

    html << R"HTML(<!doctype html>
<html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width">
<title>C++ project test report</title><style>
body{font:16px system-ui,sans-serif;background:#f2f5f9;color:#172033;margin:0;padding:32px}
main{max-width:1000px;margin:auto}h1{margin-bottom:6px}.intro{color:#526078;margin-top:0}
.cards{display:grid;grid-template-columns:repeat(auto-fit,minmax(300px,1fr));gap:18px}
section{background:white;border:1px solid #dbe2ec;border-radius:14px;padding:20px;box-shadow:0 3px 12px #1720330c}
.status{font-weight:700;color:#087443}.fail{color:#b42318}.badge{display:inline-block;padding:5px 10px;border-radius:20px;background:#e7f7ee}
svg{width:100%;height:auto}.muted{color:#65738a;font-size:14px}table{border-collapse:collapse;width:100%;margin-top:12px}
th,td{text-align:left;padding:8px;border-bottom:1px solid #e5eaf1}th{background:#f7f9fc}
</style></head><body><main><h1>Project test report</h1>
<p class="intro">Visual summary generated by the C++ test executable from the AxisData class and tests/fixtures/scores.csv.</p>
)HTML";

    const bool allPassed = axisPassed && csvPassed;
    html << "<p class=\"status " << (allPassed ? "" : "fail") << "\"><span class=\"badge\">"
         << (allPassed ? "PASS" : "FAIL") << "</span> Axis and CSV fixture checks</p>\n<div class=\"cards\">\n";

    html << "<section><h2>AxisData test " << (axisPassed ? "✓" : "✗") << "</h2>"
         << "<p>Range 0–100; the value 50 should scale to 0.5.</p>"
         << "<svg viewBox=\"0 0 600 190\" role=\"img\" aria-label=\"Axis range and midpoint test\">"
         << "<line x1=\"60\" y1=\"85\" x2=\"540\" y2=\"85\" stroke=\"#526078\" stroke-width=\"4\"/>";
    const int positions[] = {60, 180, 300, 420, 540};
    const char* tickLabels[] = {"0", "25", "50", "75", "100"};
    for (int i = 0; i < 5; ++i)
        html << "<line x1=\"" << positions[i] << "\" y1=\"75\" x2=\"" << positions[i]
             << "\" y2=\"96\" stroke=\"#526078\"/><text x=\"" << positions[i]
             << "\" y=\"120\" text-anchor=\"middle\" fill=\"#526078\">" << tickLabels[i] << "</text>";
    html << "<circle cx=\"" << 60 + midpoint * 480 << "\" cy=\"85\" r=\"11\" fill=\"#e76f51\"/>"
         << "<text x=\"300\" y=\"158\" text-anchor=\"middle\" fill=\"#172033\">scaleValue(50) = "
         << midpoint << "</text></svg><p class=\"muted\">Checks default range, setters/getters, ticks, labels, and scaling.</p></section>\n";

    html << "<section><h2>DataLoader CSV test " << (csvPassed ? "✓" : "✗") << "</h2>"
         << "<p>Loaded records from the CSV fixture and checked its header and sample rows.</p>"
         << "<table><thead><tr><th>Name</th><th>Score</th><th>Group</th></tr></thead><tbody>";
    for (std::size_t i = 1; i < rows.size(); ++i) {
        if (rows[i].size() >= 3)
            html << "<tr><td>" << rows[i][0] << "</td><td>" << rows[i][1]
                 << "</td><td>" << rows[i][2] << "</td></tr>";
    }
    html << "</tbody></table><svg viewBox=\"0 0 600 230\" role=\"img\" aria-label=\"Scores from CSV shown as bars\">";
    html << "<line x1=\"45\" y1=\"185\" x2=\"575\" y2=\"185\" stroke=\"#526078\"/>";
    const int barX[] = {105, 225, 345, 465};
    for (std::size_t i = 1; i < rows.size() && i <= 4; ++i) {
        if (rows[i].size() < 3) continue;
        const int score = std::stoi(rows[i][1]);
        const int barHeight = score * 1;
        html << "<rect x=\"" << barX[i - 1] << "\" y=\"" << 185 - barHeight
             << "\" width=\"64\" height=\"" << barHeight << "\" rx=\"5\" fill=\"#4587c7\"/>"
             << "<text x=\"" << barX[i - 1] + 32 << "\" y=\"" << 178 - barHeight
             << "\" text-anchor=\"middle\" fill=\"#172033\">" << score << "</text>"
             << "<text x=\"" << barX[i - 1] + 32 << "\" y=\"208\" text-anchor=\"middle\" fill=\"#526078\">"
             << rows[i][0] << "</text>";
    }
    html << "</svg><p class=\"muted\">Bars show the score values parsed from the fixture.</p></section></div></main></body></html>\n";
}

} // namespace

int main() {
    AxisData axis;
    double midpoint = 0.0;
    const bool axisPassed = axisChecks(axis, midpoint);
    projectname::CsvDataLoader loader("scores.csv");
    loader.load();
    const auto rows = loader.getData();
    const bool csvPassed = csvChecks(rows);
    writeSvgReport(rows, axisPassed, csvPassed, midpoint);
    writeReport(rows, axisPassed, csvPassed, midpoint);
    return axisPassed && csvPassed ? 0 : 1;
}
