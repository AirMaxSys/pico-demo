add_executable(UDM main.c)

pico_enable_stdio_usb(UDM 1)
pico_enable_stdio_uart(UDM 0)
target_include_directories(UDM PUBLIC ../common)
target_link_libraries(UDM PUBLIC pico_stdlib hardware_pwm pico_com_lib)
pico_add_extra_outputs(UDM)
