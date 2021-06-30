#include <adc.h>
#include <avr/io.h>

#include <bit_operations.h>

void adc_init(int pin)
{
    // enable ADC-hardware module
    _set_bit(ADCSRA, ADEN);

    // set multiplexer-bits
    // (currently only ADC0-15 in single ended input-mode are supported)
    switch (pin)
    {
    // ADC0
    case 0:
        ADMUX = (ADMUX & 0x70) | 0x00;
        _clear_bit(ADCSRB, MUX5);
        break;
    // ADC1
    case 1:
        ADMUX = (ADMUX & 0x70) | 0x01;
        _clear_bit(ADCSRB, MUX5);
        break;
    // ADC2
    case 2:
        ADMUX = (ADMUX & 0x70) | 0x02;
        _clear_bit(ADCSRB, MUX5);
        break;
    // ADC3
    case 3:
        ADMUX = (ADMUX & 0x70) | 0x03;
        _clear_bit(ADCSRB, MUX5);
        break;
    // ADC4
    case 4:
        ADMUX = (ADMUX & 0x70) | 0x04;
        _clear_bit(ADCSRB, MUX5);
        break;
    // ADC5
    case 5:
        ADMUX = (ADMUX & 0x70) | 0x05;
        _clear_bit(ADCSRB, MUX5);
        break;
    // ADC6
    case 6:
        ADMUX = (ADMUX & 0x70) | 0x06;
        _clear_bit(ADCSRB, MUX5);
        break;
    // ADC7
    case 7:
        ADMUX = (ADMUX & 0x70) | 0x07;
        _clear_bit(ADCSRB, MUX5);
        break;
    // ADC8
    case 8:
        ADMUX = (ADMUX & 0x70) | 0x00;
        _set_bit(ADCSRB, MUX5);
        break;
    // ADC9
    case 9:
        ADMUX = (ADMUX & 0x70) | 0x01;
        _set_bit(ADCSRB, MUX5);
        break;
    // ADC10
    case 10:
        ADMUX = (ADMUX & 0x70) | 0x02;
        _set_bit(ADCSRB, MUX5);
        break;
    // ADC11
    case 11:
        ADMUX = (ADMUX & 0x70) | 0x03;
        _set_bit(ADCSRB, MUX5);
        break;
    // ADC12
    case 12:
        ADMUX = (ADMUX & 0x70) | 0x04;
        _set_bit(ADCSRB, MUX5);
        break;
    // ADC13
    case 13:
        ADMUX = (ADMUX & 0x70) | 0x05;
        _set_bit(ADCSRB, MUX5);
        break;
    // ADC14
    case 14:
        ADMUX = (ADMUX & 0x70) | 0x06;
        _set_bit(ADCSRB, MUX5);
        break;
    // ADC15
    case 15:
        ADMUX = (ADMUX & 0x70) | 0x07;
        _set_bit(ADCSRB, MUX5);
        break;
    }

    // use internal AVCC
    _set_bit(ADMUX, REFS0);

    // set prescaler to be 128 meaning 125kHz sample-rate (perfect for 10bit solution)
    _set_bit(ADCSRA, ADPS2);
    _set_bit(ADCSRA, ADPS1);
    _set_bit(ADCSRA, ADPS0);
}

uint16_t adc_read_analog()
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