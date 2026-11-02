cmake_minimum_required(VERSION 3.16)
project(Group5DataVisualization LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_library(dataviz
    src/axis.cpp
    src/countplot.cpp
    src/data_loader.cpp
    src/histogram.cpp
    src/kde.cpp
)
add_library(dataviz::dataviz ALIAS dataviz)
target_include_directories(dataviz PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(dataviz PUBLIC cxx_std_17)

add_executable(kde_unit_test
    tests/KDE_plot_test.cpp
)
target_link_libraries(kde_unit_test PRIVATE dataviz::dataviz)
add_test(NAME kde_unit_test COMMAND kde_unit_test)

add_executable(data_loader_unit_test
    tests/data_loader_test.cpp
)
target_link_libraries(data_loader_unit_test PRIVATE dataviz::dataviz)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/fixtures/scores.csv
    ${CMAKE_CURRENT_BINARY_DIR}/scores.csv
    COPYONLY
)
add_test(NAME data_loader_unit_test COMMAND data_loader_unit_test)

add_executable(axis_unit_test
    tests/axis_test.cpp
)
target_link_libraries(axis_unit_test PRIVATE dataviz::dataviz)
add_test(NAME axis_unit_test COMMAND axis_unit_test)

add_executable(histogram_unit_test tests/histogram_test.cpp)
target_link_libraries(histogram_unit_test PRIVATE dataviz::dataviz)
add_test(NAME histogram_unit_test COMMAND histogram_unit_test)

add_executable(countplot_unit_test tests/countplot_test.cpp)
target_link_libraries(countplot_unit_test PRIVATE dataviz::dataviz)
add_test(NAME countplot_unit_test COMMAND countplot_unit_test)

add_executable(visual_test_report
    tests/visual_test_report.cpp
)
target_link_libraries(visual_test_report PRIVATE dataviz::dataviz)
add_test(NAME visual_test_report COMMAND visual_test_report)
set_tests_properties(visual_test_report PROPERTIES
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(library_demo examples/library_demo.cpp)
target_link_libraries(library_demo PRIVATE dataviz::dataviz)

install(TARGETS dataviz EXPORT datavizTargets)
install(DIRECTORY include/ DESTINATION include)
install(EXPORT datavizTargets
    NAMESPACE dataviz::
    DESTINATION lib/cmake/dataviz
)
