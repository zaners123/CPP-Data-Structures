cmake_minimum_required(VERSION 3.10)
project(testbench)

set(CMAKE_CXX_STANDARD 11)
include_directories("${PROJECT_SOURCE_DIR}")
#include(/home/zaners123/code/CLionProjects/testbench/structures.h)
add_executable(testbench main.cpp)