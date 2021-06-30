#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include <adc.h>
#include <bit_operations.h>
#include <uart.h>

int main()
{
    // set PD0 to be intput
    _clear_bit(DDRD, PD0);

    // initialize uart-communication
    uart_init(9600);
    adc_init(2);

    char str[100];

    while (1)
    {
        uint16_t raw_value = adc_read_analog();
        float value = (raw_value / 1024.0f * 5.0f * 1000.0f - 21.7) / 10.0f;
        sprintf(str, "%f°C\n", value);
        uart_puts(str);
        sprintf(str, "%d\n", raw_value);
        uart_puts(str);
        _delay_ms(1000);
    }

    return 0;
}