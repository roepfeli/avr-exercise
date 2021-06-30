#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include <uart.h>

static void setup_interrupt()
{
    // external interrupt on INT0, rising-edge
    _set_bit(EICRA, ISC00);
    _set_bit(EICRA, ISC01);

    // enable INT0
    _set_bit(EIMSK, INT0);
}

ISR(INT0_vect) { }

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

    while (1)
    {
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_mode();
        _delay_ms(200);
        uart_puts("End of loop. Someone must have woke me up!");
        _delay_ms(200);
    }

    return 0;
}