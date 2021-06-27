#include <Arduino.h>
#include <avr/wdt.h>

// active-high:
static int button = 21;

void setup()
{
    pinMode(button, INPUT);
    Serial.begin(9600);
    Serial.println("Reset!");
    attachInterrupt(2, &interrupt, RISING);
    wdt_enable(WDTO_4S);
}

void interrupt()
{
    Serial.println("Button-pressed: Kick the dog!");
    wdt_reset();
}

void loop() { }