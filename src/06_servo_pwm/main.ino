#include <Arduino.h>
#include <Servo.h>

static int servo_pin = 8;

static Servo servo;

void setup()
{
    pinMode(servo_pin, OUTPUT);
    servo.attach(servo_pin, 600, 2400);
}

void loop()
{
    servo.write(0);
    delay(100000);
    servo.write(180);
    delay(100000);
}