# Week 4 group report 


## Objective

Extend the Week 3 data visualization library so categorical frequency and percentage summaries can be saved as SVG bar charts.

## Week 4 feature in this project copy

- Added `PercentagePlot`, which calculates category percentages and implements the shared `Plot::summary()` interface.
- Added SVG output to `CountPlot` and `PercentagePlot`, including XML escaping and an empty-data message.
- Updated the count plot example to print percentage results and write `count_plot.svg` and `percentage_plot.svg`.
- Added the new implementation to the `dataviz` CMake library target.

## Member contributions
Asiimwe Allan Mark: integration, review, group coordination, and test evidence. Akora Sheenaz N: CSV loading and numeric-column handling. Baryashaba Ruth: axis interface and scaling. Kabega Nestroy: KDE class and evaluation. Lena Stacy: histogram class and bin behavior. Kabayaga Davinah: categorical count plot. Kasai Hawla: data cleaning requirements and validation proposal. Ainebyoona Joshua: test plan and execution record. Agola Jolly Martha: examples and usage guide.


## AI assistance and references

AI assistance was used to draft a learning-oriented implementation and report structure.
