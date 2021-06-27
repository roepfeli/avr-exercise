#include "./include/uart.h"

#include <avr/io.h>
#include <stdint.h>

void uart_putc(char c)
{
    // wait for transmit-buffer to be empty
    while (!_get_bit(UCSR0A, UDRE0))
        ;

    // write byte to buffer
    UDR0 = c;
}

void uart_puts(char* str)
{
    int index = 0;

    for (int i = 0; str[i] != '\0'; ++i)
    {
        uart_putc(str[index]);
        ++index;
    }
}

uint8_t uart_receive()
{
    // wait for receive-buffer to be full
    while (!_get_bit(UCSR0A, RXC0))
        ;

    return UDR0;
}

void uart_init(uint16_t baudrate)
{
    uint16_t real_baudrate = (uint16_t)(16000000.0f / 16.0f / baudrate - 1.0f);

    // set baudrate
    UBRR0H = (unsigned char)(real_baudrate >> 8);
    UBRR0L = (unsigned char)real_baudrate;

    // enable receiver and transmitter
    _set_bit(UCSR0B, RXEN0);
    _set_bit(UCSR0B, TXEN0);

    // set data-format of UART-frame: 8-data, 1-stop bits
    _set_bit(UCSR0C, USBS0);
}