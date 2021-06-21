#include <avr/io.h>

    .section .text

    .global main

SETUP_TIMER:
    ; configure harware timer0
    ; normal mode + overflow interrupt
    ; clk/1024

    ; TCCR0B = 0x05;
    ldi r18, 0x05
    out 0x25, r18

    ; TIMSK0 = 0x01;
    ldi r18, 0x01

    ; have to use ST because the IN/OUT opcode can only
    ; access the first 64 IO-registers
    ; this (r27,r26) seems to be X...
    ldi r27, 0x00
    ldi r26, 0x6e
    st X, r18

    ; sei();
    sei

    .global TIMER0_OVF_vect

__vector_default:
TIMER0_OVF_vect:
    in r18, 0x05
    ldi r19, 0xff
    eor r18, r19
    out 0x05, r18
    reti

main:
    jmp SETUP_TIMER
    ; DDRB = 0xff;
    ldi r18, 0xff
    out 0x05, r18

BLINK:
    jmp BLINK
    .end