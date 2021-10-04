cmake_minimum_required(VERSION 3.1)

project(main)
 
set(CMAKE_C_FLAGS "-Wall -Wpedantic -Wextra")
set(CMAKE_C_FLAGS_RELEASE_INIT "$(CMAKE_C_FLAGS) -O2 -DNDEBUG")
set(CMAKE_C_FLAGS_DEBUG_INIT "$(CMAKE_C_FLAGS) -g -DDEBUG")

include_directories(inc)
file(GLOB SOURCES "./src/*.c")

add_executable(main ${SOURCES})