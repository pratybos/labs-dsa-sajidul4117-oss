# CMake build file for the Algorithm Playground project.
# Same style as my weekly labs.
cmake_minimum_required(VERSION 3.16)
project(algorithm_playground LANGUAGES CXX)

# Use C++20, the same standard as my labs.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# "dsa" is a header-only library: it has no .cpp files, just the headers
# in include/dsa/. INTERFACE means "anyone who links me gets my include path".
add_library(dsa INTERFACE)
target_include_directories(dsa INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# The single console program for this project.
add_executable(playground main.cpp)
target_link_libraries(playground PRIVATE dsa)
