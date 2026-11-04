# Group 5 C++ Data Visualization Project

A C++17 learning project that provides a reusable `dataviz` library for loading simple CSV data and exploring data-analysis and visualization components. The library target contains CSV loading, axis scaling, kernel density estimation (KDE), a text histogram, and categorical CountPlot SVG rendering. `library_demo` shows several components through the shared library target.

## Project goals

- Organize C++ code into reusable components with clear interfaces.
- Read and inspect simple CSV data.
- Practice classes, encapsulation, inheritance, and polymorphism.
- Check component behavior with small, repeatable tests.

## Current features

- `CsvDataLoader` reads comma-separated text into rows of strings.
- `AxisData` stores an axis range, label, ticks, and tick labels; `scaleValue` maps a value into a normalized position.
- `KDE` calculates Gaussian kernel density estimates for numeric input.
- `TextHistogram` counts integer observations and returns a text representation.
- `CountPlot` counts categories and returns SVG markup.
- CMake builds the `dataviz` library and links six registered test programs to it, covering CSV loading, axis scaling, KDE, histogram, CountPlot, and a visual report.

The `dataviz` target provides a public include directory and can be installed with CMake. See [tests/README.md](tests/README.md) for test coverage and [examples/library_demo.cpp](examples/library_demo.cpp) for a consumer example.

## Project layout

| Path | Contents |
| --- | --- |
| `include/` | Public headers for the components |
| `src/` | Implementations compiled into the `dataviz` library |
| `examples/` | Small programs demonstrating project components |
| `tests/` | CMake test targets, test sources, and a CSV fixture |
| `data/` | Data files and output folder used by project work |
| `reports/` | Group and individual reports, figures, and project documentation |

## Requirements

- CMake 3.16 or newer
- A C++17 compiler
- A CMake-supported build tool

The commands below use a MinGW compiler available on `PATH`. If your compiler is installed elsewhere, set `CMAKE_CXX_COMPILER` to its actual path as shown below. Each computer needs its own fresh build directory because CMake caches the selected compiler path.

## Build and run the tests

Open PowerShell in the project root and run:

```powershell
$compiler = (Get-Command g++).Source
cmake -S . -B build-local -G "MinGW Makefiles" `
  -DCMAKE_CXX_COMPILER="$compiler"
cmake --build build-local --parallel 4
ctest --test-dir build-local --output-on-failure
```

If `Get-Command g++` cannot find the compiler, install a C++17 MinGW toolchain or add its `bin` folder to `PATH`, then open a new terminal. For an existing build folder that reports a missing compiler, configure into a new folder such as `build-local` instead of reusing the old cache.

Run CTest only after the build completes successfully. To run one test, add its name filter; for example:

```powershell
ctest --test-dir build-local --output-on-failure -R "^kde_unit_test$"
```

The registered tests are:

| Test | Main behavior checked |
| --- | --- |
| `kde_unit_test` | KDE density values and invalid inputs |
| `axis_unit_test` | Axis defaults, range and label accessors, and value scaling |
| `data_loader_unit_test` | CSV fixture, row parsing, blank fields, and missing-file behavior |
| `histogram_unit_test` | Integer frequencies, rendered text, negative values, and empty input |
| `countplot_unit_test` | Counts, summary, SVG output/escaping, and invalid rendering cases |
| `visual_test_report` | Axis midpoint and CSV fixture checks; creates an HTML and SVG summary |

After the visual test runs, open the report with:

```powershell
Start-Process -FilePath '.\build-testing\test-results\index.html'
```

## Current limitations

- The CSV loader splits fields at commas and does not support quoted commas or multiline quoted fields.
- KDE results are numeric; the KDE test does not draw a density curve.


## Member Contributions

| Member | Reported contribution | Commit evidence |
|---|---|---|
| Asiimwe Allan Mark | Project setup, integration, coordination, and testing | `703a803`, `cb7304b`, `1894ad3` |
| Akora Sheenaz N | CSV data loading | `f8fa532`, `869ef65`, `24bb970` |
| Baryashaba Ruth | Axis interface and scaling | `002dcf0`, `8bd304c`, `065e3e8` |
| Kabega Nestroy | KDE implementation and evaluation | `d2c50d0`, `2f1ab05`, `ec23d2b` |
| Stacy-Lena | Histogram work | `2a020b2`, `e6f1208` |
| Kabayaga Davinah | CountPlot and SVG visualization | `fad62a6`, `ccf18ed`, `c146bf9` |
| Kasai Hawla | Data-cleaning proposal and CountPlot work | `f7cdf06`, `e287ac9`, `8d20616` |
| Ainebyoona Joshua | Test work | `113a704` |
| Agola Jolly Martha | Examples and usage guidance | `1c6d4c4`, `ce8b440`, `7d014e6` |
We can check commits using
git show --stat number

## AI use

AI tools were used as development support to explain CMake and the project’s test structure, help diagnose the CSV loader interface, and revise documentation as well as assisting in building different features that were out of the learning scope.

## References

- cppreference.com, [C++ Standard Library](https://en.cppreference.com/w/cpp/standard_library) — standard headers and library components.
- cppreference.com, [Input/output library](https://en.cppreference.com/w/cpp/io/) — file and string streams.
- seaborn, [KDE plot documentation](https://seaborn.pydata.org/generated/seaborn.kdeplot.html) — kernel density estimate concepts.
- NumPy, [Histogram documentation](https://numpy.org/doc/stable/reference/generated/numpy.histogram.html) — binning and counting values.
- Matplotlib, [Histogram function documentation](https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.hist.html) — histogram concepts.

## License

This project is distributed under the MIT License. See [LICENSE](LICENSE).
