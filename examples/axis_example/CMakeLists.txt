
cmake_minimum_required(VERSION 3.16)

project(axis_examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(axis_example
    main.cpp
)

enable_testing()
add_test(NAME axis_example_runs COMMAND axis_example)