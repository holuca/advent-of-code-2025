cmake_minimum_required(VERSION 3.16)
project(AdventOfCode2025 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(aoc
    src/main.cpp
    src/day01.cpp
    src/day02.cpp
    src/day03.cpp
    src/day04.cpp
    src/day05.cpp
    src/day06.cpp
    src/day07.cpp
    src/day08.cpp
    src/util.cpp
)
