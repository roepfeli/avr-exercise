#include <Arduino.h>

// active-high:
static int s_temperature_sensor = A2;

void setup()
{
    pinMode(s_temperature_sensor, INPUT);
    Serial.begin(9600);
}

void loop()
{
    uint16_t raw_value = analogRead(s_temperature_sensor);
    float value = (raw_value / 1024.0f * 5.0f * 1000.0f - 21.7) / 10.0f;
    Serial.print(value);
    Serial.println("°C");
    Serial.println(raw_value);
    delay(1000);
}