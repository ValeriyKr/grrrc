cmake_minimum_required(VERSION 3.4)
project(grrrc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic")

set(SOURCE_FILES
    src/Lexer.cpp
    )

include_directories("include")

add_executable(main ${SOURCE_FILES})
