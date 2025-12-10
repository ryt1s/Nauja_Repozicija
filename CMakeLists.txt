cmake_minimum_required(VERSION 3.10)

project(Work_with_files)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include folder
include_directories(include)

# ------------------------
# PAGRINDINĖ PROGRAMA
# ------------------------
add_executable(program
    src/main.cpp
    src/io.cpp
    src/student.cpp
)

# ------------------------
# ABSTRACT DEMO
# ------------------------
add_executable(demo
    src/demo_abstract.cpp
    src/io.cpp
    src/student.cpp
)

# ------------------------
# UNIT TESTAI (CATCH2 v2)
# ------------------------
add_executable(test_runner
    tests/test_student.cpp
    src/student.cpp
    src/io.cpp
)

# Kad testuose būtų galima include "catch.hpp"
target_include_directories(test_runner PRIVATE tests)
