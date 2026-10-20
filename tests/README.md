# Testing guide

This guide describes what can be built and tested on the current `testing` branch, how to run each test, and where to view the graphical report.

## Build the test programs

Run these PowerShell commands from the project root. The compiler paths below are for MSYS2 UCRT64; adjust them if MSYS2 is installed elsewhere.

```powershell
cmake -S . -B build-testing -G "MinGW Makefiles" `
  -DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe `
  -DCMAKE_MAKE_PROGRAM=C:/msys64/ucrt64/bin/mingw32-make.exe
cmake --build build-testing --parallel 4
```

## Run each registered test

Run all four tests:

```powershell
ctest --test-dir build-testing --output-on-failure
```

Run one test at a time:

```powershell
ctest --test-dir build-testing --output-on-failure -R "^kde_unit_test$"
ctest --test-dir build-testing --output-on-failure -R "^axis_unit_test$"
ctest --test-dir build-testing --output-on-failure -R "^data_loader_unit_test$"
ctest --test-dir build-testing --output-on-failure -R "^visual_test_report$"
```

What each test checks:

| CTest test | Code exercised | Checks |
| --- | --- | --- |
| `kde_unit_test` | `KDE` class | Rejects empty data and invalid bandwidth; checks Gaussian density values. |
| `axis_unit_test` | `AxisData` class and `scaleValue` | Checks defaults, range and label setters/getters, tick labels, invalid ranges, and scaled positions. |
| `data_loader_unit_test` | `projectname::load_csv_data` | Checks the CSV fixture plus empty/missing files, row shapes, blank fields, and line endings. |
| `visual_test_report` | `AxisData` and `projectname::load_csv_data` | Rechecks the axis midpoint and fixture records, then writes the graphical report files. |

The test programs instantiate the available classes (`KDE` and `AxisData`) and check their public behavior. The DataLoader is currently a namespace function, so it is tested by calling the function and checking the returned rows.

## View graphical results

After `ctest` completes, open the full report in a browser:

```powershell
Start-Process -FilePath '.\build-testing\test-results\index.html'
```

Or open the standalone vector graphic:

```powershell
Start-Process -FilePath '.\build-testing\test-results\summary.svg'
```

The report shows the AxisData 0–100 scale and the 50 → 0.5 position, plus the scores read from `tests/fixtures/scores.csv` in a table and bar chart. CTest reports pass/fail; the HTML and SVG are visual summaries of the Axis and DataLoader fixture checks.

The KDE unit test currently checks numeric results only. It does not produce a KDE curve graphic. Run it with the command above to verify the calculations.

## Other plot code on this branch

`src/histogram` is a standalone text histogram program, not a CMake target or registered test. You can compile and run it manually:

```powershell
cmake -E make_directory build-testing
C:/msys64/ucrt64/bin/g++.exe .\src\histogram -o .\build-testing\histogram.exe
.\build-testing\histogram.exe
```

It prints an asterisk histogram in the terminal; it does not create a graphical file.

`src/countplot.cpp` is not included in the CMake test build on this branch and is not ready to test as a library component: its `CountPlot` class has no public header and its source is incomplete. It must first be completed and exposed through a header. Then add a unit-test target to CMake and check category counts and its `renderSVG()` output. No CountPlot graphical report is produced by the current tests.

## Classes and polymorphism

The current branch has class-based tests for `KDE` and `AxisData`, but it does not define a shared polymorphic plot base class. `DataLoader` is a free function. The unfinished `CountPlot` class is local to its `.cpp` file, and there is no buildable `Histogram` class on this branch. Therefore the current tests cannot run a meaningful base-class/derived-class dispatch test.

When the plot classes are completed, a polymorphism test should create different plot objects through a common base-class interface and call the same virtual render or summary method on each. That verifies dynamic dispatch and each plot's output. Keep each plot's numeric/counting behavior covered by focused unit tests as well.
