cmake_minimum_required(VERSION 3.21)
project(pluss_2_2)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(libs/SafeInt)
add_subdirectory(libs/googletest)
add_subdirectory(tests)
enable_testing()
include_directories(libs/SafeInt/Test)
include_directories(libs/googletest/googletest/include)

add_library(calc_lib STATIC comm.cpp comm.h )
add_executable(Calculator main.cpp)
target_link_libraries(Calculator calc_lib)

