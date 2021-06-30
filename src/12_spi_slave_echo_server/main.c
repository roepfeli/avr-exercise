#include <avr/io.h>
#include <util/delay.h>

#include <bit_operations.h>

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

static void spi_init_slave()
{
    // this will only work on atemga328p. Layout is different between MMCU's

    // set SCK, MOSI, SS as input. MISO as output.
    _clear_bit(DDRB, PB5); // SCK
    _clear_bit(DDRB, PB3); // MOSI
    _set_bit(DDRB, PB4); // MISO
    _clear_bit(DDRB, PB2); // SS

    // enable SPI
    _set_bit(SPCR, SPE);
}

int main()
{
    spi_init_slave();

    while (1)
    {
        char c = spi_receive();
        spi_transmit(c + 1);
    }
}