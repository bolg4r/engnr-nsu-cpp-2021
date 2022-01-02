cmake_minimum_required(VERSION 3.17)
project(hasher)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_executable(hasher main.cpp Hash.cpp Hash.h)

if (MSVC)
    target_compile_options(hasher
            PRIVATE /W4
            PRIVATE /WX
            )
else()
    target_compile_options(hasher
            PRIVATE -Wall
            PRIVATE -pedantic
            PRIVATE -Werror
            )
endif()