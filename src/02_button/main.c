#include <avr/interrupt.h>
#include <avr/io.h>

#include <util/delay.h>

#include "../common/include/bit_operations.h"

static volatile uint32_t ovf_count = 0;

// sets up TIMER0 (8-bit) clk/1024-prescaler
// and activates overflow-interrupt
static void setup_timer()
{
    TCCR0B = 0x05;
    TIMSK0 = 0x01;
}

// clocked at 16MHz, one clock()-tick is 1024/(16*10**6) * 256 = 16.384ms
static uint32_t clock()
{
    return ovf_count;
}

ISR(TIMER0_OVF_vect)
{
    ++ovf_count;
}

int main()
{
    _clear_bit(DDRA, DDA0);
    _set_bit(DDRA, DDA4);

    PORTA = 0x00;

    setup_timer();
    sei();

    uint32_t timestamp = clock();

    while (1)
    {
        uint32_t crnt = clock();

        if (_get_bit(PINA, PA0) && crnt - timestamp >= 12)
        {
            _toggle_bit(PORTA, PA4);
            timestamp = crnt;
        }
    }

    return 0;
}