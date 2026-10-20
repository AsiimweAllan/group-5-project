# Week 3 Report - CountPlot

## What I did
- Merged the latest main into my `count` branch.
- Replaced my old CountPlot with the shared version, which inherits from `Plot` and lives in `namespace dataviz`.
- Split the class into `include/countplot.hpp` and `src/countplot.cpp`.
- Added `include/plot.hpp`, which CountPlot depends on.

## Files changed
- src/countplot.cpp
- include/countplot.hpp
- include/plot.hpp

## Problems and fixes
- My old countplot.cpp defined the class inside the .cpp and didn't match the shared design (no Plot parent, no summary()). I replaced it with the shared version.
- Downloaded files were renamed with `_1` because of name clashes. I removed the duplicates.
- Used `g++ -std=c++17 -Iinclude` and it compiled with no errors.

## Plan for next week
- Test CountPlot with the data loader.
- Help with integration and fixing any build errors.