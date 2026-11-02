# Group 5 Final Project Report Draft

**Project:** C++ Data Visualization Library  
**Group:** 5  
**Report date:** 2 November 2026  

## 1. Project overview

Group 5 developed a C++17 library of small reusable components for loading and summarizing data and supporting data visualization. The library is named `dataviz`. Its current components include CSV loading, axis data and scaling, Gaussian kernel density estimation, integer text histograms, and categorical count plots that can render SVG markup.

The project applies classes, encapsulation, inheritance, polymorphism, standard containers, file streams, input validation, exceptions, and CMake-based modular builds. The intended users are C++ learners or programmers who want to reuse basic data-processing and visualization components.

## 2. Objectives

- Provide components through public headers with implementations separated into source files.
- Read simple comma-separated files into a two-dimensional string table.
- Calculate normalized axis positions and numeric KDE values.
- Summarize integer and categorical values in text or SVG form.
- Build the components as a reusable CMake library and provide a consumer example.
- Test the implemented behavior and document known limitations.

## 3. Library design and implementation

The CMake target `dataviz` compiles the module implementations into one library. Its public include directory exposes the headers to client programs, and the `dataviz::dataviz` alias gives consumers a stable target name to link. The existing test executables now link to this library rather than compiling separate copies of module source files. The target also has basic CMake install rules for the library and public headers.

All library classes and helpers are exposed in the `dataviz` namespace. This provides one consistent API namespace and avoids the previous arbitrary `projectname` namespace for CSV loading. `Plot` is defined once in `include/plot.hpp`; `CountPlot` includes and derives from that shared base instead of declaring a second conflicting class with the same name.

### Main components

| Component | Purpose | Main design points |
| --- | --- | --- |
| `CsvDataLoader` | Reads lines and comma-separated cells into rows of strings. | Derives from abstract `DataLoader`; stores its table in vectors; reports file-open errors with an exception. |
| `AxisData` | Stores range, axis title, ticks, and labels. | Private state is changed through setters; `LabeledAxis` demonstrates inheritance and virtual dispatch; `scaleValue` maps an input into normalized coordinates. |
| `KDE` | Estimates numeric density at points or across a range. | Holds a vector of doubles and bandwidth; validates empty data and invalid bandwidth/range arguments. |
| `TextHistogram` | Counts integer observations and formats a text histogram. | Reusable class in a public header/source pair; uses a map for the count result instead of a fixed frequency array. |
| `Plot` and `CountPlot` | Provides common plot labels and a polymorphic plot interface; counts categories and generates SVG markup. | The shared abstract base owns title/axis labels; CountPlot implements summary and SVG rendering. |

The `examples/library_demo.cpp` program acts as a consumer of the shared library. It demonstrates axis scaling, KDE evaluation, text histogram output, and category counting. It currently does not write an SVG file.

## 4. Object-oriented and C++ concepts

- **Encapsulation:** `AxisData`, `KDE`, and `TextHistogram` keep implementation data private and expose operations through public functions.
- **Inheritance and abstraction:** `CsvDataLoader` specializes the abstract `DataLoader`; `LabeledAxis` specializes `AxisData`; plot types implement the shared abstract `Plot` interface.
- **Polymorphism:** virtual functions allow derived implementations to be called through a base-class interface.
- **STL containers:** vectors represent observations and rows; maps hold category and histogram frequencies; pairs represent KDE range coordinates.
- **References and const:** `getData()` returns a const reference to avoid copying the full table while preventing mutation through that accessor.
- **Validation and exceptions:** invalid KDE parameters and file-open failures are reported to callers rather than silently accepted.
- **CMake library target:** clients link one project target instead of rebuilding source files independently.

Templates for broader numerical-type support were considered but not implemented in this revision. KDE still stores `double`, axis scaling accepts `double`, and the histogram handles `int`. The group can identify template candidates and justify them as future work without claiming that the current code accepts all numerical types.

## 5. Build and demonstration

The project uses CMake 3.16 or later and a C++17 compiler. Example commands for the documented MSYS2 UCRT64 MinGW setup are:

```powershell
cmake -S . -B build-testing -G "MinGW Makefiles" `
  -DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe `
  -DCMAKE_MAKE_PROGRAM=C:/msys64/ucrt64/bin/mingw32-make.exe
cmake --build build-testing --parallel 4
.\build-testing\library_demo.exe
```

The library demo shows the user-facing API. The registered CTest suite covers KDE, axis behavior, CSV parsing, and a visual report for axis/CSV fixture checks.

**Final local clean-build result:** A fresh `build-review` directory configured and compiled successfully on Windows PowerShell with MSYS2 MinGW g++ 16.2.0 and CMake 4.5.0-rc1. The build command was `cmake --build build-review --parallel 4`; all library, demo, and registered test targets compiled. The six test results are recorded below. This was a local machine check; outside-machine review remains pending.  
**Outside-machine review:** [Group: record reviewer context, machine/toolchain, README steps followed, result, and issues. Do not mark complete until an outside tester has run it.]  
**Latest local test results:** All six registered tests passed on 2 November 2026 in the project-local `build-review` directory. Environment: MSYS2 MinGW g++ 16.2.0 and CMake 4.5.0-rc1. Command: `ctest --test-dir build-review --output-on-failure`. No tests failed. This is a local result, not the required outside-machine review.

## 6. Test coverage and remaining work

The six registered tests cover `KDE`, `AxisData`, `CsvDataLoader`, `TextHistogram`, and `CountPlot`, plus a generated visual report for axis and CSV fixture behavior. Histogram tests check frequency counts, text output, negative values, and empty input. CountPlot tests check counts, summary output, SVG generation and XML escaping, and invalid render inputs. All six tests passed in the local environment recorded above.

 The CSV loader uses simple comma splitting and does not support quoted commas or multiline quoted fields. KDE produces numeric values but does not draw a density curve. The library demo currently prints CountPlot's summary but does not save its SVG output. The Week 4 group report describes a `PercentagePlot` feature, but there is no `PercentagePlot` class or implementation in the current source tree; confirm whether that report is outdated or the feature still needs to be added.

## 7. Team contributions and collaboration

| Member | Reported focus | Evidence and contribution confirmation |
| --- | --- | --- |
| Asiimwe Allan Mark | Integration, review, coordination, and test evidence. 
| Akora Sheenaz N | CSV loading and numeric-column handling. 
| Baryashaba Ruth | Axis interface and scaling. 
| Kabega Nestroy | KDE class and evaluation. 
| Lena Stacy | Histogram class and bin behavior. 
| Kabayaga Davinah | Categorical CountPlot. 
| Kasai Hawla | Data-cleaning requirements and validation proposal. | [Member: identify whether this was a proposal or implementation, with evidence.] |
| Ainebyoona Joshua | Test plan and execution record. 
| Agola Jolly Martha | Examples and usage guide. 

##How the team collaborated: 
We used different branches each member working on their own branch, thereafter we made sure to push all work the branch thereafter created a pull request which was approved by another member 
Proof of contribution
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

## 8. Challenges and resolutions

Earlier weekly reports describe difficulties integrating changes without interfering with teammates' commits and uneven familiarity with the code. A Week 3 report also left its actual-progress section unfinished. The codebase showed inconsistent namespaces, two different `dataviz::Plot` declarations, and test executables compiling their own module sources instead of sharing a library target. This revision addresses those integration problems by unifying the namespace, consolidating the Plot base, and linking existing tests and the consumer demo to `dataviz`.

## 9. AI-use declaration

AI tools have been used during this project. Existing weekly documentation mentions ChatGPT/Copilot assistance for code understanding, implementation support, debugging, and report/example wording.

## 10. Conclusion

The project now has a shared CMake library target that brings together its principal data loading, numerical, axis, histogram, and categorical plotting components. The existing tests and a consumer example use that same target. 
