cmake_minimum_required(VERSION 3.26)
project(SillyDB C)

set(CMAKE_C_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)


add_executable(start
        src/main.c
        src/controller.c
        src/utils.c
        src/storage.c
        src/socket.c
        src/hashmap.c
)
