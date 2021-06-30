CC = avr-gcc
CFLAGS = -g -Os -Wall
MMCU = atmega2560
CPU_FREQ = 16000000
INCLUDE = -I./include/

SOURCES := $(wildcard ./*.c)
OBJECTS := $(patsubst ./%.c, ./%.o, $(SOURCES))

build: $(OBJECTS)
	# $(CC) $(CFLAGS) $(INCLUDE) -DF_CPU=$(CPU_FREQ) -mmcu=$(MMCU) -c $< -o $(subst .c,.o, $<)
	# avr-gcc -I./include/ -DF_CPU=16000000 -mmcu=atmega2560 -c $< $(CFLAGS) -o $(subst .c,.o, $<)

.PHONY: clean build

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.elf
