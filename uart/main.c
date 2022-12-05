// Test UART - by usb (tinyUsb library)
#include <stdio.h>
#include "pico/stdlib.h"

int main()
{
    stdio_init_all();
    for (;;) {
        printf("Hello, pico!\n");
        sleep_ms(1000);
    }
    return 0;
}
