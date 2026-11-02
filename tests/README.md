# Building and testing

The current CMake project builds the shared `dataviz` library, a consumer example, and six registered test programs.

## Configure and build

From the project root in PowerShell, configure using the compiler installed on your machine. For MSYS2 UCRT64 MinGW:

```powershell
cmake -S . -B build-testing -G "MinGW Makefiles" `
  -DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe `
  -DCMAKE_MAKE_PROGRAM=C:/msys64/ucrt64/bin/mingw32-make.exe
cmake --build build-testing --parallel 4
```

Run the registered tests after the build succeeds:

```powershell
ctest --test-dir build-testing --output-on-failure
```

## Registered coverage

| Test | Library component | Current checks |
| --- | --- | --- |
| `kde_unit_test` | `dataviz::KDE` | Density values, empty input, invalid bandwidth, and invalid range arguments. |
| `axis_unit_test` | `dataviz::AxisData` | Defaults, range and label accessors, invalid ranges, ticks, labels, and normalized scaling. |
| `histogram_unit_test` | `dataviz::TextHistogram` | Integer frequencies, rendered text, negative values, and empty input. |
| `countplot_unit_test` | `dataviz::CountPlot` | Category counts, summary text, SVG output and escaping, and invalid rendering inputs. |
| `data_loader_unit_test` | `dataviz::CsvDataLoader` | Fixture parsing, empty/missing files, row shapes, blank fields, and line endings. |
| `visual_test_report` | `dataviz::AxisData` and `dataviz::CsvDataLoader` | Axis midpoint and CSV fixture checks; writes HTML and SVG summaries. |

All six targets are registered with CTest. The Histogram and CountPlot tests were added on 2 November 2026; run the commands above to repeat them alongside the original tests.

## Library demonstration

Build and run the combined consumer example:

```powershell
cmake --build build-testing --target library_demo
.\build-testing\library_demo.exe
```

It demonstrates axis scaling, numeric KDE evaluation, text histogram output, and a categorical count summary. It does not write an SVG file.

After running `ctest`, open the generated visual report:

```powershell
Start-Process -FilePath '.\build-testing\test-results\index.html'
```

The report covers the axis midpoint and CSV fixture only. The KDE test checks numeric results; it does not draw a KDE curve. The current CSV parser splits on commas and does not support quoted commas or multiline quoted fields.
