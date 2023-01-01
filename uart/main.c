#include <stdio.h>
#include <assert.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART0_TX_PIN    0
#define UART0_RX_PIN    1

#define UART1_TX_PIN    4
#define UART1_RX_PIN    5

uart_inst_t *uart_dev = uart0;

int fputc(int ch, FILE *f);
int bsp_uart_init(uart_inst_t *dev, uint baudrate);

int main()
{
    stdio_init_all();
    bsp_uart_init(uart_dev, 115200);

    for (;;) {
        printf("Hello, pico w!\n");
        sleep_ms(1000);
    }
    return 0;
}

int bsp_uart_init(uart_inst_t *dev, uint baudrate)
{
    const uint data_bits = 8, stop_bits = 1, parity = UART_PARITY_NONE;
    const bool is_rx_irq_enable = false, is_tx_irq_enable = false;
    const bool is_fifo_enable = true;

    assert(dev == uart0 || dev == uart1);

    if (uart0 == dev) {
        gpio_set_function(UART0_TX_PIN, GPIO_FUNC_UART);
        gpio_set_function(UART0_RX_PIN, GPIO_FUNC_UART);
    } else {
        gpio_set_function(UART1_TX_PIN, GPIO_FUNC_UART);
        gpio_set_function(UART1_RX_PIN, GPIO_FUNC_UART);
    }

    uart_deinit(dev);
    uart_init(dev, baudrate);
    uart_set_format(dev, data_bits, stop_bits, parity);
    uart_set_irq_enables(dev, is_rx_irq_enable, is_tx_irq_enable);
    uart_set_fifo_enabled(dev, is_fifo_enable);

    return 0;
}

/* Redirection stdlib fputc*/
int fputc(int ch, FILE *f)
{
    (void)f;
    uart_write_blocking(uart_dev, (const uint8_t *)&ch, 1);
    return ch;
}
