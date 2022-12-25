#include <stdio.h>
#include "pico/stdlib.h"
#include "spi.h"

#define SPI_BAUDRATE_1MHz   1000000

int main()
{
    stdio_init_all();
    spi_init(spi0, SPI_BAUDRATE_1MHz);

    for (;;) {
        printf("Hello, pico!\n");
        sleep_ms(1000);
    }

    return 0;
}
