cmake_minimum_required(VERSION 3.15)

# Project name and version
project(nPhys VERSION 1.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)  # Enable Qt's Meta-Object Compiler
set(CMAKE_AUTORCC ON)  # Optional: Enable Qt's resource compiler
set(CMAKE_AUTOUIC ON)  # Optional: Enable Qt's UI compiler

# Enable folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

# Set output directories
add_subdirectory(dep/pybind11)
add_subdirectory(src)