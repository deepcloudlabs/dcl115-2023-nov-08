cmake_minimum_required(VERSION 3.26)
project(module09)

set(CMAKE_CXX_STANDARD 23)

add_executable(exercise01 exercise01.cpp threadsafe_queue.cpp threadsafe_queue.h)
