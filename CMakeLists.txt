cmake_minimum_required(VERSION 3.3)
project(hw219)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp hw219.cpp)
add_executable(hw219 ${SOURCE_FILES} hw219.cpp)