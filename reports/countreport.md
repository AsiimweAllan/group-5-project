# OBJECT-ORIENTED C++ DATA VISUALIZATION



## 1. Abstract

This project presents the design and implementation of an object-oriented data visualization application using C++. The program processes categorical data, calculates the frequency and percentage of each category, and generates corresponding bar charts in Scalable Vector Graphics (SVG) format.

The application uses an abstract base class named `Plot` and two derived classes named `CountPlot` and `PercentagePlot`. These classes demonstrate the major principles of object-oriented programming, including encapsulation, inheritance, abstraction, and polymorphism.

The final implementation includes labeled axes, gridlines, numerical scales, category labels, value labels, input validation, and error handling. The application is developed using C++17 and does not require external graphics libraries.

## 2. Introduction

Data visualization is the graphical representation of information to make it easier to understand and interpret. Bar charts are commonly used to compare categories and identify patterns in datasets.

This project applies object-oriented programming techniques to develop a simple categorical data visualization system in C++.

The system takes a collection of category names, determines how frequently each category appears, calculates the percentage contribution of each category, and generates graphical representations.

SVG was selected as the output format because it produces scalable graphics that can be viewed in web browsers without requiring additional graphics libraries.

## 3. Project Objectives

The main objectives of the project were:

1. To develop a C++ application capable of processing categorical datasets.
2. To calculate the frequency of occurrence of each category.
3. To calculate the percentage contribution of each category.
4. To generate count and percentage bar charts using SVG.
5. To demonstrate encapsulation, inheritance, abstraction, and polymorphism.
6. To implement error handling and input validation.
7. To produce readable and reusable C++ code.

## 4. System Design

The application consists of three main classes: `Plot`, `CountPlot`, and `PercentagePlot`.

### 4.1 Plot Class

The `Plot` class is an abstract base class that provides common functionality for different types of plots.

It contains the following protected attributes:

- `x_label_`: Stores the horizontal axis label.
- `y_label_`: Stores the vertical axis label.
- `title_`: Stores the chart title.

It also provides the following functions:

- `setXLabel()`: Sets the horizontal axis label.
- `setYLabel()`: Sets the vertical axis label.
- `setTitle()`: Sets the chart title.
- `drawChart()`: Generates the shared SVG chart structure.
- `renderSVG()`: A pure virtual function implemented by derived classes.

The pure virtual function makes `Plot` an abstract class, meaning objects cannot be created directly from it.

### 4.2 CountPlot Class

The `CountPlot` class inherits publicly from `Plot`.

Its main responsibility is to calculate the frequency of each category and generate a frequency bar chart.

It contains:

- `data_`: A private vector storing the categorical dataset.
- `bar_color_`: A private structure storing the RGB color of the bars.

The `computeFrequencies()` method counts the occurrences of each unique category using `std::map`.

The `renderSVG()` method converts the calculated frequencies into a graphical bar chart using the shared drawing function.

### 4.3 PercentagePlot Class

The `PercentagePlot` class also inherits publicly from `Plot`.

Its purpose is to calculate the percentage contribution of each category and generate a percentage bar chart.

The `computePercentages()` method determines the frequency of each category and divides it by the total number of observations.

The `renderSVG()` method produces a bar chart with a vertical scale ranging from 0% to 100%.

### 4.4 Class Relationship

The inheritance structure is shown below:

```text
                 Plot
           (Abstract Class)
                  |
          -----------------
          |               |
      CountPlot      PercentagePlot
          |               |
   Frequency Chart   Percentage Chart
```

Both derived classes inherit common functionality from `Plot` and implement their own versions of `renderSVG()`.

## 5. Algorithms and Calculations

### 5.1 Frequency Calculation

Frequency represents the number of times a particular category appears in the dataset.

The frequency calculation is performed using the `computeFrequencies()` method.

The program loops through every category and increments its corresponding count in a map.

Mathematically:

**fᵢ = Number of occurrences of category i**

For example, consider the dataset:

Apple, Banana, Apple, Orange, Banana, Apple.

The calculated frequencies are:

| Category | Frequency |
|---|---:|
| Apple | 3 |
| Banana | 2 |
| Orange | 1 |
| **Total** | **6** |

### 5.2 Percentage Calculation

The percentage contribution of each category is calculated using:

**Percentage = (Category frequency / Total observations) × 100%**

For Apple:

Percentage = (3 / 6) × 100 = 50%

For Banana:

Percentage = (2 / 6) × 100 = 33.33%

For Orange:

Percentage = (1 / 6) × 100 = 16.67%

The results are summarized below.

| Category | Frequency | Percentage |
|---|---:|---:|
| Apple | 3 | 50.0% |
| Banana | 2 | 33.3% |
| Orange | 1 | 16.7% |
| **Total** | **6** | **100.0%** |

### 5.3 SVG Generation

SVG stands for Scalable Vector Graphics. It is an XML-based format used to represent graphical elements such as lines, rectangles, and text.

The application generates SVG markup using C++ string streams.

The `drawChart()` function performs the following operations:

1. Validates the chart dimensions and dataset.
2. Determines the available plotting area.
3. Draws the chart title and background.
4. Draws horizontal gridlines and numerical tick labels.
5. Draws the horizontal and vertical axes.
6. Calculates the height and position of each bar.
7. Draws rectangular bars for the categories.
8. Adds category names and values above the bars.
9. Adds axis labels.
10. Returns the completed SVG document.

The `escapeXML()` function converts special characters into XML-safe representations to prevent malformed output.

## 6. Object-Oriented Programming Concepts Applied

### 6.1 Encapsulation

Encapsulation involves combining data and related functions within a class while restricting direct access to internal data.

In this project, `CountPlot` and `PercentagePlot` contain private data members such as `data_` and `bar_color_`.

These attributes cannot be accessed directly from outside their respective classes.

This protects the internal state of objects and improves code organization.

### 6.2 Inheritance

Inheritance allows a derived class to reuse properties and functions from an existing class.

Both `CountPlot` and `PercentagePlot` inherit from the `Plot` class.

For example:

`class CountPlot final : public Plot`

This allows `CountPlot` to use the common chart labels and drawing functionality defined in the base class.

Inheritance reduces code duplication and improves maintainability.

### 6.3 Polymorphism

Polymorphism allows objects of different derived classes to be accessed through a common base-class interface.

The application stores plot objects using:

`std::vector<std::unique_ptr<Plot>> plots;`

Although the vector contains pointers to `Plot`, the objects are instances of `CountPlot` and `PercentagePlot`.

When `renderSVG()` is called through a base-class pointer, the appropriate derived-class implementation is executed.

This is runtime polymorphism.

### 6.4 Abstraction

Abstraction involves exposing essential functionality while hiding unnecessary implementation details.

The `Plot` class contains the pure virtual function:

`virtual std::string renderSVG(int width = 800, int height = 500) const = 0;`

This defines a common interface that all derived plot classes must implement.

The user can generate charts without needing to understand every internal calculation.

### 6.5 Resource Management

The program uses `std::unique_ptr` to manage dynamically allocated objects automatically.

This eliminates the need to manually delete plot objects and reduces the risk of memory leaks.

File streams are also automatically closed when they go out of scope.

## 7. Program Implementation

The final program is implemented in a single C++ source file named `main.cpp`.

The program uses standard C++ libraries, including:

- `<vector>` for storing categorical observations.
- `<map>` for storing category frequencies and percentages.
- `<memory>` for managing polymorphic objects.
- `<fstream>` for writing SVG files.
- `<sstream>` for constructing SVG output.
- `<algorithm>` for mathematical comparisons.
- `<stdexcept>` for exception handling.
- `<iomanip>` for formatting numerical values.

The `main()` function creates the dataset, constructs the chart objects, sets their labels and titles, and saves the generated graphics.

The application produces two output files:

**count_plot.svg** — A frequency bar chart.

**percentage_plot.svg** — A percentage bar chart.

## 8. Results and Discussion

The application was evaluated using the following categorical dataset:

Apple, Banana, Apple, Orange, Banana, Apple.

The frequency calculation produced three occurrences of Apple, two occurrences of Banana, and one occurrence of Orange.

The percentage calculation produced 50.0%, 33.3%, and 16.7%, respectively.

### 8.1 Count Plot

The count plot displays the frequencies of the three fruit categories.

The horizontal axis represents fruit categories, while the vertical axis represents their frequencies.

Apple has the tallest bar because it occurs three times, followed by Banana with two occurrences and Orange with one occurrence.

**Figure 1: Count plot showing the frequency of fruit categories.**

*Insert the generated count_plot.svg chart here.*

### 8.2 Percentage Plot

The percentage plot displays the relative contribution of each fruit category to the total dataset.

The vertical axis ranges from 0% to 100%.

Apple contributes the largest percentage at 50.0%, followed by Banana at 33.3% and Orange at 16.7%.

**Figure 2: Percentage plot showing the relative distribution of fruit categories.**

*Insert the generated percentage_plot.svg chart here.*

### 8.3 Discussion

The results demonstrate that the application correctly converts categorical observations into numerical summaries and graphical representations.

The frequency plot is useful for comparing absolute occurrences, while the percentage plot is useful for understanding the relative contribution of each category.

Using a shared base class makes it possible to process both plot types through the same interface.

## 9. Testing and Validation

The program was compiled using the C++17 standard with compiler warnings enabled.

The following table summarizes the verification status.

| Test | Expected Result | Status |
|---|---|---|
| C++17 compilation | Program compiles successfully | Passed |
| Frequency calculation | Apple 3, Banana 2, Orange 1 | Passed |
| Percentage calculation | 50.0%, 33.3%, 16.7% | Passed |
| SVG generation | Two SVG files created | Passed |
| Empty dataset | Descriptive exception during rendering | Implemented |
| Invalid chart dimensions | Invalid dimensions rejected | Implemented |
| Excessive categories | More than 20 categories rejected | Implemented |
| File-writing errors | Error reported and nonzero exit | Implemented |

The first four checks were verified using the supplied sample dataset. The remaining cases are handled in the implementation but were not separately executed as test cases.

## 10. Improvements Made to the Initial Program

Several improvements were introduced during the development process.

First, labeled axes and numerical scales were added to make the graphs easier to interpret.

Second, horizontal gridlines and values above the bars were introduced to improve readability.

Third, a reusable drawing function was implemented in the base class to reduce duplication between the two derived classes.

Fourth, exception handling was introduced to manage invalid chart dimensions, empty datasets, excessive categories, and file-writing failures.

Fifth, XML escaping was implemented to ensure special characters in titles and labels do not produce malformed SVG markup.

Finally, the application was organized around a common abstract interface, improving maintainability and demonstrating runtime polymorphism.

## 11. Limitations and Future Improvements

Although the application meets its main objectives, several limitations remain.

The program currently uses a fixed sample dataset rather than accepting interactive user input or reading from a CSV file.

The chart generator supports a maximum of 20 categories, and long category names are shortened when displayed.

Possible future improvements include adding CSV file import, customizable chart colors, automatic text wrapping, interactive tooltips, and automated unit testing.

These improvements would make the application more flexible and suitable for larger datasets.

## 12. Conclusion

The project successfully demonstrates the development of a categorical data visualization application using object-oriented programming in C++.

The system calculates category frequencies and percentages and generates corresponding SVG bar charts.

The implementation demonstrates encapsulation, inheritance, polymorphism, and abstraction through a reusable abstract base class and two derived classes.

Additional features such as input validation, exception handling, labeled axes, and numerical scales improve the quality and reliability of the generated graphics.

Overall, the project provides a practical demonstration of how object-oriented programming can be applied to data processing and graphical visualization.

## Appendix: Project Deliverables

The final submission consists of:

1. `main.cpp` — Complete C++ source code.
2. `count_plot.svg` — Generated frequency bar chart.
3. `percentage_plot.svg` — Generated percentage bar chart.
4. Final project report — Documentation of the design, implementation, and results.
