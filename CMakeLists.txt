cmake_minimum_required(VERSION 3.15)

project(RP2040_FUN C CXX ASM)

set(PICO_SDK_PATH "../sdk/pico-sdk")
set(CMAKE_C_COMPILER "/usr/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/arm-none-eabi-g++")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include(pico_sdk_import.cmake)

pico_sdk_init()

add_compile_options(-Wall
    -Wno-format
    -Wno-unused-funtion
    -Wno-maybe-uninitialized)

add_subdirectory(common)
# targets
add_subdirectory(uart)
# add_subdirectory(spi_master)
# add_subdirectory(ultrasonic_distance_measurement)
