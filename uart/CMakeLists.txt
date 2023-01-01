cmake_minimum_required(VERSION 3.15)
add_executable(uart main.c)

target_include_directories(uart PUBLIC ../common)
target_link_libraries(uart PUBLIC pico_stdlib pico_com_lib)
pico_add_extra_outputs(uart)
