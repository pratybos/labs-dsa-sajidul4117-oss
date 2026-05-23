cmake_minimum_required(VERSION 3.16)
project(week04_binary_tree_traversal LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# INTERFACE library: header-only data structures, used to share include paths across targets
add_library(dsa INTERFACE)
target_include_directories(dsa INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(week04 main.cpp)
target_link_libraries(week04 PRIVATE dsa)

add_executable(week04_tests tests.cpp)
target_link_libraries(week04_tests PRIVATE dsa)
