cmake_minimum_required(VERSION 3.21)
project(pluss_2_2)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(libs/SafeInt)


add_executable(Calculator main.cpp comm.cpp comm.h)
