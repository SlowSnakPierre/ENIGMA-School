cmake_minimum_required(VERSION 3.27)
project(Pendu C)

set(CMAKE_C_STANDARD 11)

add_executable(Pendu main.c dico.h dico.c)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()