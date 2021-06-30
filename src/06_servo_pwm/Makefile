# TODO: make parameter to use for other avr-mmcu's

.PHONY: clean

arduino:
	mkdir -p tmp
	mv main.c tmp
	arduino --upload main.ino
	mv tmp/main.c .
	rmdir tmp

c:
	avr-gcc -g -Os -Wall -DF_CPU=16000000 -mmcu=atmega2560 -o main.elf main.c
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avrdude -D -p atmega2560 -c wiring -U main.hex -P /dev/ttyACM0 -b 115200

assembly:
	avr-gcc -g -Os -Wall -DF_CPU=16000000 -mmcu=atmega2560 -o main.elf main.s
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avrdude -D -p atmega2560 -c wiring -U main.hex -P /dev/ttyACM0 -b 115200

clean:
	rm -f *.elf
	rm -f *.o
	rm -f *.hex