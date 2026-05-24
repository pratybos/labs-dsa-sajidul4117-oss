cmake_minimum_required(VERSION 3.16)
project(week05_bst LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# INTERFACE library: header-only data structures, shared include paths
add_library(dsa INTERFACE)
target_include_directories(dsa INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(week05 main.cpp)
target_link_libraries(week05 PRIVATE dsa)

add_executable(week05_tests tests.cpp)
target_link_libraries(week05_tests PRIVATE dsa)
