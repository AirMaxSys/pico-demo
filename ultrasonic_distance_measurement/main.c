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

#define RP2040_GPIO_NUM 29U
#define PICO_LED_TRIG() gpio_xor_mask(1U<<25)

uint udm_slice_num;

void pico_led_init(void)
{
    // LED PIN:25
    gpio_init(25);
    gpio_set_dir(25, true);

}

static uint udm_calc_distance(uint us)
{
    uint res = 0;

    // time out 38ms means over sensor measurement range(about 4m)
    if (us >= 38000) {
        puts("Info: UDM over range!");
        return 0;
    }
    // Sound speed 340m/s (we can use temperature sensor to correct sound speed)
    res = 340*(us>>1);  // micrometer
    return res;
}

static void udm_trigger_pin_init(uint gpio)
{
    assert(gpio <= RP2040_GPIO_NUM);
    gpio_init(gpio);
    gpio_set_dir(gpio, true);
}

static void udm_trigger_10us_pulse(uint gpio)
{
    assert(gpio <= RP2040_GPIO_NUM);
    gpio_put(gpio, true);
    busy_wait_us(10);
    gpio_put(gpio, false);
}

void udm_echo_pulse_meas_callback(void)
{
    irq_clear(PWM_IRQ_WRAP);
    uint pulse_width = pwm_get_counter(udm_slice_num);
    udm_calc_distance(pulse_width);
}

static void udm_irq_setup(void)
{
    irq_set_exclusive_handler(PWM_IRQ_WRAP, udm_echo_pulse_meas_callback);
    irq_set_enabled(PWM_IRQ_WRAP, true);
}

static uint udm_echo_pulse_measurement_init(uint gpio)
{
    assert(gpio <= RP2040_GPIO_NUM);
    pwm_config pc = {0};
    uint pwm_slice_num = pwm_gpio_to_slice_num(gpio);

    gpio_set_function(gpio, GPIO_FUNC_PWM);
    pwm_init(pwm_slice_num, &pc, false);
    udm_irq_setup();

    return pwm_slice_num;
}

int main()
{
    // Default CPU frequency is 125MHz
    // printf("CPU freq:%ld\r\n", clock_get_hz(clk_sys));

    const uint8_t udm_trig_pin = 0, udm_echo_pin = 1;

    stdio_init_all();
    pico_led_init();
    // UDM trigger pin0
    udm_trigger_pin_init(udm_trig_pin);
    udm_slice_num = udm_echo_pulse_measurement_init(udm_echo_pin);

    while (1) {
        // UDM starting
        udm_trigger_10us_pulse(0);
        PICO_LED_TRIG();
        sleep_ms(1000);
    }
}
