cmake_minimum_required(VERSION 3.16)
project(C5_s21_decimal C)

set(CMAKE_C_STANDARD 11)

add_library(decimal_library STATIC src/s21_*.c)  # create libdecimal_library.a
target_link_libraries(decimal_library m) # m - math library

add_executable(run_tests src/test.c )
target_link_libraries(run_tests check decimal_library)