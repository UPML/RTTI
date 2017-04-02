cmake_minimum_required(VERSION 3.6)
project(RTTI)

set(CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_FLAGS "-fno-rtti")

set(SOURCE_FILES main.cpp)
add_executable(RTTI ${SOURCE_FILES})