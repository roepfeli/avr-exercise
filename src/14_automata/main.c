#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

#include <bit_operations.h>
#include <timer.h>
#include <uart.h>

typedef enum
{
    START,
    CLAP1_DETECTED,
    CLAP2_PENDING,
} states;

typedef enum
{
    CLAP_DETECT,
    TIMER100_EXPIRE,
    TIMER300_EXPIRE,
    NONE,
} events;

static volatile bool s_timer100_active = false;
static volatile int s_timer100 = 0;
static volatile bool s_timer300_active = false;
static volatile int s_timer300 = 0;
static volatile states s_crnt_state = START;

void start_clap_detect()
{
    uart_puts("start_clap_detect\n");
    _delay_ms(50);
    s_timer100 = clock();
    s_timer100_active = true;
    s_crnt_state = CLAP1_DETECTED;
}

void idle() { }

void clap1_detected_timer100_expire()
{
    s_timer100_active = false;
    s_timer300 = clock();
    s_timer300_active = true;
    s_crnt_state = CLAP2_PENDING;
}

void clap2_pending_timer300_expire()
{
    s_timer300_active = false;
    s_crnt_state = START;
}

void clap2_pending_clap_detect()
{
    s_timer300_active = false;
    _toggle_bit(PORTD, PD0);
    s_crnt_state = START;
}

void (*automata[3][4])(void) = {
    // CLAP_DETECT, TIMER100_EXPIRE, TIMER300_EXPIRE, NONE
    {
        start_clap_detect,
        idle,
        idle,
        idle,
    }, // START
    {
        idle,
        clap1_detected_timer100_expire,
        idle,
        idle,
    }, // CLAP1_DETECTED
    {
        clap2_pending_clap_detect,
        idle,
        clap2_pending_timer300_expire,
        idle,
    } // CLAP2_PENDING
};

int main()
{
    cli();
    _set_bit(DDRD, PD0);
    _clear_bit(DDRA, PA2);
    _clear_bit(PORTD, PD0);
    uart_init(9600);
    timer_init();
    sei();

    uart_puts("Reset\n");

    while (true)
    {
        events event = NONE;

        if (clock() - s_timer300 >= 300 && s_timer300_active)
        {
            event = TIMER300_EXPIRE;
            uart_puts("timer300_expire\n");
            _delay_ms(50);
        }

        if (clock() - s_timer100 >= 100 && s_timer100_active)
        {
            event = TIMER100_EXPIRE;
            uart_puts("timer100_expire\n");
            _delay_ms(50);
        }

        if (_get_bit(PINA, PA2))
        {
            event = CLAP_DETECT;
            uart_puts("clap_detect\n");
            _delay_ms(50);
        }

        automata[s_crnt_state][event]();
    }
}