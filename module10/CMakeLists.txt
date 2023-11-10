cmake_minimum_required(VERSION 3.26)
project(module10)

set(CMAKE_CXX_STANDARD 23)

add_executable(exercise01 exercise01.cpp country.cpp country.h city.cpp city.h world-util.cpp world-util.h)
add_executable(exercise02 exercise02.cpp country.cpp country.h city.cpp city.h world-util.cpp world-util.h)
