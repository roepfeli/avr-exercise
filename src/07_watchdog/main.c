#include <avr/interrupt.h>
#include <avr/wdt.h>

#include <uart.h>

static void setup_interrupt()
{
    // external interrupt on INT0, rising-edge
    _set_bit(EICRA, ISC00);
    _set_bit(EICRA, ISC01);

    // enable INT0
    _set_bit(EIMSK, INT0);
}

ISR(INT0_vect)
{
    wdt_reset();
    uart_puts("Button pressed: Kick the dog!\n");
    // reti();
}

int main()
{
    cli();
    // set PD0 to be intput
    _clear_bit(DDRD, PD0);

    // initialize uart-communication
    uart_init(9600);
    uart_puts("Reset!\n");

    setup_interrupt();

    sei();

    wdt_enable(WDTO_4S);

    while (1)
    { }

    return 0;
}