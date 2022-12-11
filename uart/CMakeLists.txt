add_executable(uart main.c)

pico_enable_stdio_usb(uart 1)
pico_enable_stdio_uart(uart 0)

target_link_libraries(uart pico_stdlib)
pico_add_extra_outputs(uart)
