#include <avr/io.h>
#include <util/delay.h>

#include "../common/include/bit_operations.h"

static void setup_pwm()
{
    // set clock-source to be clk/1024
    _set_bit(TCCR0B, CS02);
    _clear_bit(TCCR0B, CS01);
    _set_bit(TCCR0B, CS00);

    // set mode of operation to be PWM, phase correct 8-bit: top 0xff
    _set_bit(TCCR0A, WGM00);

    // set OC0A on cmp-match upcounting and clear OC0A on cmp-match downcounting
    _set_bit(TCCR0A, COM0A0);
    _set_bit(TCCR0A, COM0A1);
}

static void set_duty_cycle(uint8_t duty_cycle)
{
    OCR0A = duty_cycle;
}

int main()
{
    setup_pwm();
    _set_bit(DDRB, PB7);

    while (1)
    {
        // software-pwm

        // for (uint16_t i = 0; i < 50; ++i)
        // {
        //     _set_bit(PORTB, PB7);
        //     _delay_us(1000);
        //     _clear_bit(PORTB, PB7);
        //     _delay_us(19000);
        // }

        // for (uint16_t i = 0; i < 50; ++i)
        // {
        //     _set_bit(PORTB, PB7);
        //     _delay_us(2000);
        //     _clear_bit(PORTB, PB7);
        //     _delay_us(18000);
        // }

        // hardware pwm (not really duty-cycle, sets the OCR0A-register directly...)
        set_duty_cycle(243);
        _delay_ms(1000);
        set_duty_cycle(230);
        _delay_ms(1000);
    }

    return 0;
}