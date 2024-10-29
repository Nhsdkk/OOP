cmake_minimum_required(VERSION 3.10)

set(SubProjectName "lab_4")

add_library(${SubProjectName}_lib
        ./src/Triangle.h
        ./src/Octagon.h
        ./src/Point.h
        ./src/Figure.h
        ./src/Figure.cpp
        ./src/FigureArray.h
)
add_executable(${SubProjectName}_exe main.cpp)

target_link_libraries(${SubProjectName}_exe PRIVATE ${SubProjectName}_lib)

add_executable(${SubProjectName}_tests tests/tests.cpp)
target_link_libraries(${SubProjectName}_tests ${SubProjectName}_lib gtest_main)

add_test(NAME {SubProjectName}_Tests COMMAND ${SubProjectName}_tests)