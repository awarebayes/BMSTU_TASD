cmake_minimum_required(VERSION 3.20)
project(lab_05 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-Wall -Wpedantic -Wextra")
set(CMAKE_C_FLAGS_RELEASE_INIT "$(CMAKE_C_FLAGS) -O2 -DNDEBUG")
set(CMAKE_C_FLAGS_DEBUG_INIT "$(CMAKE_C_FLAGS) -g -DDEBUG")

include_directories(inc)
file(GLOB SOURCES "./src/*.c")

add_executable(lab_05 ${SOURCES})
# TARGET_LINK_LIBRARIES(lab_05 metalang99 interface99)