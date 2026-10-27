# Group 5 C++ Data Visualization Project

A C++17 learning project for reading simple CSV data and exploring reusable components for data analysis and visualization. The repository contains CSV loading, axis scaling, kernel density estimation (KDE), a standalone text histogram, examples, and CMake-based tests.

## Project goals

- Organize C++ code into reusable components with clear interfaces.
- Read and inspect simple CSV data.
- Practice classes, encapsulation, inheritance, and polymorphism.
- Check component behavior with small, repeatable tests.

## Current features

- `CsvDataLoader` reads comma-separated text into rows of strings.
- `AxisData` stores an axis range, label, ticks, and tick labels; `scaleValue` maps a value into a normalized position.
- `KDE` calculates Gaussian kernel density estimates for numeric input.
- `src/histogram` is a standalone program that prints a text histogram.
- CMake builds four registered test programs for the CSV loader, axis scaling, KDE, and a combined visual test report.

The current CMake configuration builds the test programs. The repository does not yet build all components as one integrated, installed visualization library. The text histogram is also separate from the CMake test targets. See [tests/README.md](tests/README.md) for the exact test coverage and histogram instructions.

## Project layout

| Path | Contents |
| --- | --- |
| `include/` | Public headers for the components |
| `src/` | Component implementations and standalone histogram source |
| `examples/` | Small programs demonstrating project components |
| `tests/` | CMake test targets, test sources, and a CSV fixture |
| `data/` | Data files and output folder used by project work |
| `reports/` | Group and individual reports, figures, and project documentation |
| `cmake/` | CMake package configuration template |

## Requirements

- CMake 3.16 or newer
- A C++17 compiler
- A CMake-supported build tool

The commands below use MSYS2 UCRT64 MinGW on Windows. Change the compiler and make paths if MSYS2 is installed elsewhere.

## Build and run the tests

Open PowerShell in the project root and run:

```powershell
cmake -S . -B build-testing -G "MinGW Makefiles" `
  -DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe `
  -DCMAKE_MAKE_PROGRAM=C:/msys64/ucrt64/bin/mingw32-make.exe
cmake --build build-testing --parallel 4
ctest --test-dir build-testing --output-on-failure
```

Run CTest only after the build completes successfully. To run one test, add its name filter; for example:

```powershell
ctest --test-dir build-testing --output-on-failure -R "^kde_unit_test$"
```

The registered tests are:

| Test | Main behavior checked |
| --- | --- |
| `kde_unit_test` | KDE density values and invalid inputs |
| `axis_unit_test` | Axis defaults, range and label accessors, and value scaling |
| `data_loader_unit_test` | CSV fixture, row parsing, blank fields, and missing-file behavior |
| `visual_test_report` | Axis midpoint and CSV fixture checks; creates an HTML and SVG summary |

After the visual test runs, open the report with:

```powershell
Start-Process -FilePath '.\build-testing\test-results\index.html'
```

## Current limitations

- The CSV loader splits fields at commas and does not support quoted commas or multiline quoted fields.
- The histogram is a standalone text program rather than an integrated library component.
- KDE results are numeric; the KDE test does not draw a density curve.
- CountPlot and other planned chart components are not currently part of the registered CMake test suite.

## AI use

AI tools were used as development support to explain CMake and the project’s test structure, help diagnose the mismatch between the CSV loader tests and the `CsvDataLoader` class interface, and revise project documentation. The updated tests were rebuilt and run with CTest. Group members are responsible for reviewing, understanding, and approving AI-assisted changes before submitting the project.

## References

- cppreference.com, [C++ Standard Library](https://en.cppreference.com/w/cpp/standard_library) — standard headers and library components.
- cppreference.com, [Input/output library](https://en.cppreference.com/w/cpp/io/) — file and string streams.
- seaborn, [KDE plot documentation](https://seaborn.pydata.org/generated/seaborn.kdeplot.html) — kernel density estimate concepts.
- NumPy, [Histogram documentation](https://numpy.org/doc/stable/reference/generated/numpy.histogram.html) — binning and counting values.
- Matplotlib, [Histogram function documentation](https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.hist.html) — histogram concepts.

## License

This project is distributed under the MIT License. See [LICENSE](LICENSE).
