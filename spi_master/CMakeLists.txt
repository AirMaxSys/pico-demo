cmake_minimum_required(VERSION 3.15)
add_executable(spi_master main.c)

target_link_libraries(spi_master pico_stdlib)
pico_add_extra_outputs(spi_master)