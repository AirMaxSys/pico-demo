add_executable(UDM main.c)

target_link_libraries(UDM pico_stdlib)
pico_add_extra_outputs(UDM)
