#include <Arduino.h>

static int led = 24;

void setup()
{
    pinMode(led, OUTPUT);
}

void loop()
{
    digitalWrite(led, !digitalRead(led));
    delay(1000);
}