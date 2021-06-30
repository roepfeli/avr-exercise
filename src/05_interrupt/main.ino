#include <Arduino.h>

static int s_button = 21;
static int s_count = 0;
static long s_timestamp = -200;

void setup()
{
    pinMode(s_button, INPUT);
    Serial.begin(9600);
    attachInterrupt(2, &interrupt, RISING);
}

void interrupt()
{
    long crnt = millis();

    if (crnt - s_timestamp >= 200)
    {
        Serial.println(++s_count);
        s_timestamp = crnt;
    }
}

void loop()
{
    // unsigned long crnt = millis();

    // poll solution

    // if (digitalRead(s_button) && crnt - s_timestamp >= 400)
    // {
    //     Serial.println(++s_count);
    //     s_timestamp = crnt;
    // }
}