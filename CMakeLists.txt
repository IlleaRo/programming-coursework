cmake_minimum_required(VERSION 3.23)
project(cursework_1)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
add_executable(cursework_1 main.cpp FileNode.h Root.h Fraction.cpp Fraction.h)
