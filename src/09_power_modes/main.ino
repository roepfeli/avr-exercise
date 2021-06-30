#include <Arduino.h>
#include <avr/sleep.h>

// active-high:
static int button = 21;

void setup()
{
    pinMode(button, INPUT);
    Serial.begin(9600);
    Serial.println("Reset!");
    attachInterrupt(2, &interrupt, RISING);
}

// this activates
void interrupt() { }

void loop()
{
    // go to sleep (power-down-mode)
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
    delay(200);
    Serial.println("End of loop. Someone must have woke me up!");
    delay(200);
}