#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

#include <bit_operations.h>

static volatile uint32_t s_count = 0;

void timer_init()
{
    // clk/64
    _set_bit(TCCR0B, CS01);
    _set_bit(TCCR0B, CS00);

    // activate timer0-overflow interrupt
    _set_bit(TIMSK0, TOIE0);
}

ISR(TIMER0_OVF_vect)
{
    // clk/64 + OVF 8-bit => 1.024ms per overflow ~1ms
    s_count++;
}

uint32_t clock()
{
    return s_count;
}