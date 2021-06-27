CC = avr-gcc
CFLAGS = -g -Os -Wall
MMCU = atmega2560
CPU_FREQ = 16000000
INCLUDE = -I./include/

OBJECTS = $(wildcard ./*.c)

build: $(OBJECTS)
	$(CC) $(INCLUDE) -DF_CPU=$(CPU_FREQ) -mmcu=$(MMCU) -c $< $(CFLAGS) -o $(subst .c,.o, $<)

.PHONY: clean build

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.elf
