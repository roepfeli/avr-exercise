#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "../common_c/include/bit_operations.h"
#include "../common_c/include/uart.h"

static void setup_adc()
{
    // enable ADC-hardware module
    _set_bit(ADCSRA, ADEN);

    // use ADC2 in single-input mode
    _set_bit(ADMUX, MUX1);

    // use internal AVCC
    _set_bit(ADMUX, REFS0);

    // set prescaler to be 128 meaning 125kHz sample-rate (perfect for 10bit solution)
    _set_bit(ADCSRA, ADPS2);
    _set_bit(ADCSRA, ADPS1);
    _set_bit(ADCSRA, ADPS0);
}

static uint16_t read_analog()
{
    // start a conversion
    _set_bit(ADCSRA, ADSC);

    // wait for conversion to be finished
    while (_get_bit(ADCSRA, ADSC))
        ;

    uint16_t low = ADCL;
    uint16_t high = ADCH << 8;

    uint16_t result = high | low;

    return result;
}

int main()
{
    // set PF2 to be intput
    _clear_bit(DDRF, PF2);

    // setup ADC
    setup_adc();

    // initialize uart-communication
    uart_init(9600);

    char str[64] = {0};

    while (1)
    {
        float analog_value = read_analog() / 1024.0f * 5.0f;
        sprintf(str, "%fV\n", analog_value);
        uart_puts(str);
        _delay_ms(1000);
    }

    return 0;
}