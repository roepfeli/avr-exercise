static int s_led = 26;
static int s_button = 22;

static unsigned long s_timestamp = 0;

void setup()
{
    pinMode(s_button, INPUT);
    pinMode(s_led, OUTPUT);

    digitalWrite(s_led, LOW);
}

void loop()
{
    unsigned long crnt = millis();

    if (digitalRead(s_button) && crnt - s_timestamp >= 200)
    {
        s_timestamp = crnt;
        digitalWrite(s_led, !digitalRead(s_led));
    }
}