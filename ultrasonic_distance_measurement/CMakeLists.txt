add_executable(UDM main.c)

pico_enable_stdio_usb(UDM 1)
pico_enable_stdio_uart(UDM 0)
target_link_libraries(UDM pico_stdlib hardware_pwm)
pico_add_extra_outputs(UDM)
