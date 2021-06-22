#include <Arduino.h>

static int trigger = 34;
static int echo = 32;

void setup()
{
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    Serial.begin(9600);
}

void loop()
{
    digitalWrite(trigger, LOW);
    delay(5);
    digitalWrite(trigger, HIGH);
    delay(10);
    digitalWrite(trigger, LOW);

    long timeElapsed = pulseIn(echo, HIGH);

    double distance = 0.034029 * timeElapsed / 2;

    Serial.print(distance);
    Serial.println("cm");
    delay(1000);
}