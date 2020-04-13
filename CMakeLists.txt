cmake_minimum_required(VERSION 2.8)
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
project(BruteForce_CalcudokuSolver)

include_directories(include)

add_executable(Solver src/main.cpp)

