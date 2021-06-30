#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>

#include "../common_c/include/bit_operations.h"

static void setup_timer()
{
    // using TIMER4

    // initialize timer-control-registers to 0x00
    TCCR4A = 0x00;
    TCCR4B = 0x00;

    // use mode of operation: CTC-mode
    _set_bit(TCCR4B, WGM42);

    // set prescaler: clk/256
    _set_bit(TCCR4B, CS42);

    // set OCR4AH/OCR4AL to match 0.5 Hz,
    // when external clock-source = 16mHz
    OCR4AH = 0xf4;
    OCR4AL = 0x24;

    // enable OCR4A interrupt
    _set_bit(TIMSK4, OCIE4A);
}

ISR(TIMER4_COMPA_vect)
{
    _toggle_bit(PORTA, PA2);
}

int main()
{
    cli();

    // use PA2 as output (led-pin)
    _set_bit(DDRA, PA2);
    _clear_bit(PORTA, PA2);

    setup_timer();
    sei();

    while (1)
    { }

    return 0;
}