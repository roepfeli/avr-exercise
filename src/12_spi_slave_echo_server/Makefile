# TODO: make parameter to use for other avr-mmcu's

.PHONY: clean

arduino:
	mkdir -p tmp
	mv main.c tmp
	arduino --upload main.ino
	mv tmp/main.c .
	rmdir tmp

c:
	avr-gcc -g -Os -Wall -DF_CPU=16000000 -mmcu=atmega328p -L../common_c/ -I../common_c/include -o main.elf main.c
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avrdude -D -p atmega328p -c arduino -U main.hex -P /dev/ttyACM1 -b 115200

assembly:
	avr-gcc -g -Os -Wall -DF_CPU=16000000 -mmcu=atmega328p -o main.elf main.s
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avrdude -D -p atmega328p -c arduino -U main.hex -P /dev/ttyACM1 -b 115200

clean:
	rm -f *.elf
	rm -f *.o
	rm -f *.hex