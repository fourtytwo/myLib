cmake_minimum_required(VERSION 3.2)
project(Matrix)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Matrix ${SOURCE_FILES} exceptions.h exceptions.cpp matrix.h matrix.cpp)