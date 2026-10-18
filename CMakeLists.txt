cmake_minimum_required(VERSION 3.16)
project(KDE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_executable(kde_unit_test
    tests/KDE_plot_test.cpp
    src/kde.cpp
)
target_include_directories(kde_unit_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME kde_unit_test COMMAND kde_unit_test)

add_executable(data_loader_unit_test
    tests/data_loader_test.cpp
    src/data_loader.cpp
)
target_include_directories(data_loader_unit_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/fixtures/scores.csv
    ${CMAKE_CURRENT_BINARY_DIR}/scores.csv
    COPYONLY
)
add_test(NAME data_loader_unit_test COMMAND data_loader_unit_test)

add_executable(axis_unit_test
    tests/axis_test.cpp
    src/axis.cpp
)
target_include_directories(axis_unit_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME axis_unit_test COMMAND axis_unit_test)

add_executable(visual_test_report
    tests/visual_test_report.cpp
    src/axis.cpp
    src/data_loader.cpp
)
target_include_directories(visual_test_report PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(NAME visual_test_report COMMAND visual_test_report)
set_tests_properties(visual_test_report PROPERTIES
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
