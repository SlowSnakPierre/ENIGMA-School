cmake_minimum_required(VERSION 3.27)
project(cardsgame C)

set(CMAKE_C_STANDARD 11)

add_executable(cardsgame main.c
        ansi.h
        main.h)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()