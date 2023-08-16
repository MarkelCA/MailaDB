cmake_minimum_required(VERSION 3.26)
project(SillyDB C)

set(CMAKE_C_STANDARD 11)

set(COMMON_SOURCES
        src/controller.c
        src/utils.c
        src/storage.c
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)


add_executable(SillyDB
        src/main.c
        ${COMMON_SOURCES}
)

add_executable(cli
        src/cli.c
        ${COMMON_SOURCES}
        src/storage.c
)
