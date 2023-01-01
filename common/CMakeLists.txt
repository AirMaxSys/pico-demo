cmake_minimum_required(VERSION 3.15)
add_library(pico_com_lib STATIC common.c common.h)
target_link_libraries(pico_com_lib PUBLIC pico_stdlib)