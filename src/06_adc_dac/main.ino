#include <Arduino.h>

static int potentiometer = A2;

void setup()
{
    pinMode(potentiometer, INPUT);
    Serial.begin(9600);
}

void loop()
{
    float value = analogRead(potentiometer) / 1024.0f * 5.0f;
    Serial.print(value);
    Serial.println("v");
    delay(1000);
}