#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "../common_c/include/bit_operations.h"

static void setup_timer()
{
    TCCR0B = 0x05;
    TIMSK0 = 0x01;
    sei();
}

static volatile uint8_t ovf_count = 0;

ISR(TIMER0_OVF_vect)
{
    if (++ovf_count == 50)
    {
        _toggle_bit(PORTB, PB7);
        ovf_count = 0;
    }
}

int main()
{
    // poll-version with _delay_ms()

    // _set_bit(DDRB, PB7);

    // while (1)
    // {
    //     _toggle_bit(PORTB, PB7);
    //     _delay_ms(1000);
    // }

    _set_bit(DDRB, DDB7);

    setup_timer();

    while (1)
    { }

    return 0;
}