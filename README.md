# Group 5 C++ Data Visualization Library

A small C++17 learning project for reading simple CSV data and calculating basic summaries. The project is organized as a reusable library with separate example programs. The examples print results in the terminal; the project does not currently draw charts in a graphical window.

## Features

- Read CSV rows into a two-dimensional collection of strings.
- Trim whitespace around cells and remove rows that are entirely blank.
- Store axis labels and ranges, and scale values to positions between 0 and 1.
- Estimate numeric data density using a Gaussian kernel density estimate (KDE).
- Group numeric data into histogram bins and count the values in each bin.
- Count how often each text category appears.
- Demonstrate class inheritance and polymorphism with a shared `Plot` base class and the `Histogram` and `CountPlot` classes.

## Project structure

| Folder | Contents |
| --- | --- |
| `include/` | Public class and function declarations (`.hpp` files) |
| `src/` | Implementations of the library components (`.cpp` files) |
| `examples/` | Small programs that demonstrate one component at a time |
| `data/` | Sample CSV input |
| `tests/` | Test source files from project development |
| `reports/` | Weekly group and individual report drafts |

## Requirements

- CMake 3.16 or newer
- A C++17 compiler
- A build tool supported by the CMake generator

For the current Windows setup, the commands below use the MSYS2 UCRT64 `g++` compiler and `mingw32-make`.

## Build on Windows with MinGW

Open this project folder in VS Code, open **Terminal → New Terminal**, and run these commands from the project root:

```powershell
cmake -G "MinGW Makefiles" -S . -B build-mingw -DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe -DCMAKE_MAKE_PROGRAM=C:/msys64/ucrt64/bin/mingw32-make.exe
cmake --build build-mingw
```

CMake creates the `dataviz` library and builds the example programs in `build-mingw/`.

## Run the examples

Run these commands from the project root after building:

```powershell
.\build-mingw\data_loader_example.exe .\data\sample.csv
.\build-mingw\axis_example.exe
.\build-mingw\kde_example.exe
.\build-mingw\histogram_example.exe
.\build-mingw\countplot_example.exe
.\build-mingw\polymorphism_example.exe
```

The data loader example accepts a CSV path as an argument. The other examples use small values written directly in their source files.

## Classes and how they are organized

Each class keeps related data and functions together. For example, `Histogram` stores numeric values and a bin count, then provides functions to find the minimum, maximum, and counts in each bin. Its stored values are private; other code uses its public functions to get results.

`Plot` is a parent class with a shared title and a virtual `summary()` function. `Histogram` and `CountPlot` inherit from `Plot` and provide their own version of `summary()`. The `polymorphism_example.cpp` program passes both kinds of object to the same `showSummary()` function. The function calls the correct summary implementation for the object it receives.

## Current limitations

- The CSV loader splits rows at commas. It is intended for simple CSV files and does not handle quoted commas or multiline quoted fields.
- The cleaner trims cell boundaries and removes fully blank rows. It does not decide how missing values should be replaced.
- KDE bandwidth affects how smooth the estimate looks; the current program expects the user to choose a positive bandwidth.
- The `tests/` source files are not yet registered as CMake tests. A successful build confirms the library and examples compile, but does not mean the tests have run.

## References

These sources explain the standard-library tools and data visualization concepts that can be used to study this project. Seaborn, NumPy, and Matplotlib are Python libraries; they are references for the ideas only and are not dependencies of this C++ project.

- cppreference.com, [C++ Standard Library](https://en.cppreference.com/w/cpp/standard_library) — standard headers and library components such as vectors, maps, streams, and exceptions.
- cppreference.com, [Input/output library](https://en.cppreference.com/w/cpp/io/) — file and string streams used when reading text data.
- seaborn, [KDE plot documentation](https://seaborn.pydata.org/generated/seaborn.kdeplot.html) — kernel density estimates and bandwidth.
- NumPy, [Histogram documentation](https://numpy.org/doc/stable/reference/generated/numpy.histogram.html) — dividing values into bins and counting observations.
- Matplotlib, [Histogram function documentation](https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.hist.html) — histogram examples and bin behavior.
