cmake_minimum_required(VERSION 3.15)

# Project name and version
project(nPhys VERSION 1.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)

# Enable folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set output directories
add_subdirectory(dep/pybind11)
add_subdirectory(dep/glfw)
add_subdirectory(src)