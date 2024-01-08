cmake_minimum_required(VERSION 3.27)
project(CasseBrique C)

set(CMAKE_C_STANDARD 11)

set(SDL2_PATH "C:\\Users\\thblt\\Downloads\\SDL2-2.28.5\\x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)

set(SDL2_TTF_PATH "C:\\Users\\thblt\\Downloads\\SDL2_ttf-2.20.2\\x86_64-w64-mingw32")
find_package(SDL2_ttf REQUIRED)

set(SDL2_IMAGE_PATH "C:\\Users\\thblt\\Downloads\\SDL2_image-2.6.3\\x86_64-w64-mingw32")
find_package(SDL2_image REQUIRED)

set(SDL2_MIXER_PATH "C:\\Users\\thblt\\Downloads\\SDL2_mixer-2.6.3\\x86_64-w64-mingw32")
find_package(SDL2_MIXER REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})

file(GLOB SOURCES
        inc/*.h
        inc/stds/*.h
        src/stds/*.c
        src/*.c
)

file(COPY res DESTINATION ${CMAKE_BINARY_DIR})

add_executable(CasseBrique ${SOURCE_FILES} ${SOURCES})

target_link_libraries(CasseBrique ${SDL2_LIBRARY} ${SDL2TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2MIXER_LIBRARY})