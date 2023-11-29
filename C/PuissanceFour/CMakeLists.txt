cmake_minimum_required(VERSION 3.27)
project(PuissanceFour C)

set(CMAKE_C_STANDARD 11)

add_executable(PuissanceFour main.c
        display.c
        grid.c
        game.c)
