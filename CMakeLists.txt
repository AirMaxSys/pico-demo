cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH "../sdk/pico-sdk")
set(CMAKE_C_COMPILER "/usr/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/arm-none-eabi-g++")

include(pico_sdk_import.cmake)

project(pico_test_uart C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_compile_options(-Wall
    -Wno-format
    -Wno-unused-funtion
    -Wno-maybe-uninitialized)

add_executable(uart uart/main.c)
target_link_libraries(uart pico_stdlib)

pico_enable_stdio_usb(uart 1)
pico_enable_stdio_uart(uart 0)

pico_add_extra_outputs(uart)
