#include "pico/stdlib.h"

void pico_led_init(void)
{
    // LED PIN:25
    gpio_init(25);
    gpio_set_dir(25, true);
}
