#include <avr/io.h>
#include <util/delay.h>

#include <bit_operations.h>
#include <uart.h>

static void spi_transmit(uint8_t c)
{
    // start transmit by writing data to register
    SPDR = c;

    // wait for transmit to be over
    while (!_get_bit(SPSR, SPIF))
        ;
}

static uint8_t spi_receive()
{
    // wait for transmission to be over
    while (!_get_bit(SPSR, SPIF))
        ;

    // return received data
    return SPDR;
}

static void spi_init_master()
{
    // this will only work on atemga2560. Layout is different between MMCU's

    // set SCK, MOSI, SS as output. MISO as input.
    _set_bit(DDRB, PB1); // SCK
    _set_bit(DDRB, PB2); // MOSI
    _clear_bit(DDRB, PB3); // MISO
    _set_bit(DDRB, PB0); // SS

    // set master-mode using clk/16 frequency
    _set_bit(SPCR, MSTR);
    _set_bit(SPCR, SPR0);

    // enable SPI
    _set_bit(SPCR, SPE);
}

int main()
{
    spi_init_master();

    uart_init(9600);

    _clear_bit(PORTB, PB0);

    while (1)
    {
        spi_transmit('h');
        char c1 = spi_receive();
        uart_putc(c1);
        spi_transmit('i');
        char c2 = spi_receive();
        uart_putc(c2);

        uart_putc('\n');

        _delay_ms(1000);
    }
}