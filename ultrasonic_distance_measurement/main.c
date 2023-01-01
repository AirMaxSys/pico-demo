/*******************************************************************
 * Ultrasonic distance measurement(UDM) base on HC-SR04 sensor
 * Pin layout:
 *      VCC     |   VBUS(5V)
 *      TRIG    |   PIN0
 *      EHCO    |   PIN1
 *      GND     |   GND
********************************************************************/
#include <stdio.h>
#include <assert.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "hardware/irq.h"
#include "common.h"

uint udm_slice_num;
uint distance;

static uint udm_calc_distance(uint us)
{
    uint res = 0;

    // time out 38ms means over sensor measurement range(about 4m)
    if (us >= 38000U) {
        puts("Info: UDM measurement timeout!");
        return 0;
    }
    // Sound speed 340m/s (we can use temperature sensor to correct sound speed)
    res = 170U*us;  // micrometer
    return res;
}

static void udm_trig_pin_init(uint gpio)
{
    assert(gpio <= RP2040_GPIO_NUM);
    gpio_init(gpio);
    gpio_set_dir(gpio, true);
}

static void udm_start(uint gpio)
{
    assert(gpio <= RP2040_GPIO_NUM);
    gpio_put(gpio, true);
    busy_wait_us(15);
    gpio_put(gpio, false);
}

void udm_echo_pulse_measurement_callback(uint gpio, uint32_t events)
{
    (void)gpio;
    if (events & GPIO_IRQ_EDGE_RISE) {
        pwm_set_enabled(udm_slice_num, true);
    } else {
        pwm_set_enabled(udm_slice_num, false);
        uint pulse_width = pwm_get_counter(udm_slice_num);
        pwm_set_counter(udm_slice_num, 0);
        distance = udm_calc_distance(pulse_width);
        uint mm = distance/1000;
        if (mm >= 10 && mm < 1000)
            printf("%.1fcm\r\n", mm/10.0);
        else if (mm >= 1000 && mm <= 4600)
            printf("%.2fm\r\n", mm/1000.0);
        else
            printf("Info: value[%ld] UDM measurement out of range!\r\n", mm);
    }
}

static uint udm_echo_pulse_measurement_init(uint gpio)
{
    assert(gpio <= RP2040_GPIO_NUM);
    assert(pwm_gpio_to_channel(gpio) == PWM_CHAN_B);
    pwm_config cfg = {0};
    uint pwm_slice_num = pwm_gpio_to_slice_num(gpio);

    cfg = pwm_get_default_config();
    pwm_config_set_clkdiv(&cfg, 125);
    pwm_init(pwm_slice_num, &cfg, false);
    gpio_set_irq_enabled_with_callback(gpio, \
        GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &udm_echo_pulse_measurement_callback);

    return pwm_slice_num;
}

int main()
{
    const uint8_t udm_trig_pin = 0, udm_echo_pin = 1;

    // Default CPU frequency is 125MHz
    // printf("CPU freq:%ld\r\n", clock_get_hz(clk_sys));
    
    stdio_init_all();
    pico_led_init();
    // UDM trigger pin0
    udm_trig_pin_init(udm_trig_pin);
    udm_slice_num = udm_echo_pulse_measurement_init(udm_echo_pin);

    while (1) {
        printf("test uart\r\n");
        // UDM starting
        udm_start(udm_trig_pin);
        PICO_LED_TRIG();
        sleep_ms(1000);
    }
}
