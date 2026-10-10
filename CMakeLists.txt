cmake_minimum_required(VERSION 3.16)
project(KDE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(kde_example
    examples/kde_example.cpp
    src/kde.cpp
)

add_executable(kde_test
    tests/KDE_plot_test.cpp
    src/kde.cpp
)

enable_testing()
add_test(NAME kde_example_runs COMMAND kde_example)
add_test(NAME kde_unit_test COMMAND kde_test)
