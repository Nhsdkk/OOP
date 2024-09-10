cmake_minimum_required(VERSION 3.10)

set(SubProjectName "lab_1")

add_library(${SubProjectName}_lib src/gcd.cpp)
add_executable(${SubProjectName}_exe main.cpp)

target_link_libraries(${SubProjectName}_exe PRIVATE ${SubProjectName}_lib)

add_executable(tests tests/test.cpp)
target_link_libraries(tests ${SubProjectName}_lib gtest_main)

add_test(NAME {SubProjectName}_Tests COMMAND tests)