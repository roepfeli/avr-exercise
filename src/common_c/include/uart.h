#pragma once

#include <bit_operations.h>
#include <stdint.h>

void uart_putc(char c);

void uart_puts(char* str);

uint8_t uart_receive();

void uart_init(uint16_t baudrate);