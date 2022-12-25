#include "pico/stdlib.h"

int main()
{
    // LED PIN:25
    gpio_init(25);
    gpio_set_dir(25, true);

    while (1) {
        gpio_xor_mask(1<<25);
        sleep_ms(1000);
    }
}
