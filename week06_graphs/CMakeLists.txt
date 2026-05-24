cmake_minimum_required(VERSION 3.16)
project(week06_graphs LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(dsa INTERFACE)
target_include_directories(dsa INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(week06 main.cpp)
target_link_libraries(week06 PRIVATE dsa)

add_executable(week06_tests tests.cpp)
target_link_libraries(week06_tests PRIVATE dsa)
