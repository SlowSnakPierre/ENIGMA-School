cmake_minimum_required(VERSION 3.27)
project(HelloSDL2 C)

set(CMAKE_C_STANDARD 11)

set(SDL2_PATH "C:\\Users\\thblt\\Downloads\\SDL2-2.28.5\\x86_64-w64-mingw32")
set(SDL2TTF_PATH "C:\\Users\\thblt\\Downloads\\SDL2_ttf-2.20.2\\x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "C:\\Users\\thblt\\Downloads\\SDL2_image-2.6.3\\x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)
find_package(SDL2_IMAGE REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2TTF_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

add_executable(HelloSDL2 main.c)

target_link_libraries(HelloSDL2 ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY})