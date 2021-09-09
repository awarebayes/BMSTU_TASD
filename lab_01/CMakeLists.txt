cmake_minimum_required(VERSION 3.14)

project(lab_01 C)

add_library(big_int
  big_int.c
  big_int.h
)

add_library(big_float
  big_float.c
  big_float.h
)

add_library(utils
  util.c
  util.h
  unit_tests.h
  unit_tests.c
)

add_executable(main main.c)
target_link_libraries(main PRIVATE big_int big_float)