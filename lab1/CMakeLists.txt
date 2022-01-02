cmake_minimum_required(VERSION 3.17)
project(pluss_workinghard)

set(CMAKE_CXX_STANDARD 14)

add_executable(pluss_workinghard main.cpp Hash.cpp Hash.h)

if (MSVC)
    target_compile_options(pluss_workinghard
            PRIVATE /W4
            PRIVATE /WX
            )
else()
    target_compile_options(pluss_workinghard
            PRIVATE -Wall
            PRIVATE -pedantic
            PRIVATE -Werror
            )
endif()