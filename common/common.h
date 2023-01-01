#ifndef _COMMON_
#define _COMMON_

#define RP2040_GPIO_NUM     29U

#define PICO_LED_TRIG()     gpio_xor_mask(1U<<25)

void pico_led_init(void);

#endif
