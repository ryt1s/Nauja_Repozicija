cmake_minimum_required(VERSION 3.10)

project(FirstProject VERSION 2.0 LANGUAGES CXX)

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
    src/zmogus.cpp
)

# ------------------------
# ABSTRACT DEMO
# ------------------------
add_executable(demo_abstract
    demo_abstract.cpp
    src/io.cpp
    src/student.cpp
    src/zmogus.cpp
)

# ------------------------
# UNIT TESTAI (CATCH2 v2)
# ------------------------
add_executable(test_runner
    tests/test_student.cpp
    src/student.cpp
    src/io.cpp
    src/zmogus.cpp
)

# Kad testuose būtų galima include "catch.hpp"
target_include_directories(test_runner PRIVATE tests)
