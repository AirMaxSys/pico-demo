cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico_test_uart C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_compile_options(-Wall
    -Wno-format
    -Wno-unused-funtion
    -Wno-maybe-uninitialized)

add_executable(uart-usb
    main.c)

target_link_libraries(uart-usb
    pico_stdlib)

pico_enable_stdio_usb(uart-usb 1)
pico_enable_stdio_uart(uart-usb 0)

pico_add_extra_outputs(uart-usb)

