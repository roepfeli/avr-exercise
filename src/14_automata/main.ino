#include <Arduino.h>

static int s_led_pin = 21;
static int s_microphone_sensor = 24;

typedef enum
{
    START,
    CLAP1_DETECTED,
    CLAP2_PENDING,
} states;

typedef enum
{
    CLAP_DETECT,
    TIMER100_EXPIRE,
    TIMER300_EXPIRE,
    NONE,
} events;

static volatile bool s_timer100_active = false;
static volatile int s_timer100 = 0;
static volatile bool s_timer300_active = false;
static volatile int s_timer300 = 0;
static volatile states s_crnt_state = START;

volatile void start_clap_detect()
{
    Serial.println("start_clap_detect");
    delay(50);
    s_timer100 = millis();
    s_timer100_active = true;
    s_crnt_state = CLAP1_DETECTED;
}

void idle() { }

volatile void clap1_detected_timer100_expire()
{
    s_timer100_active = false;
    s_timer300 = millis();
    s_timer300_active = true;
    s_crnt_state = CLAP2_PENDING;
}

volatile void clap2_pending_timer300_expire()
{
    s_timer300_active = false;
    s_crnt_state = START;
}

volatile void clap2_pending_clap_detect()
{
    s_timer300_active = false;
    digitalWrite(s_led_pin, !digitalRead(s_led_pin));
    s_crnt_state = START;
}

void (*automata[3][4])(void) = {
    // CLAP_DETECT, TIMER100_EXPIRE, TIMER300_EXPIRE, NONE
    {
        start_clap_detect,
        idle,
        idle,
        idle,
    }, // START
    {
        idle,
        clap1_detected_timer100_expire,
        idle,
        idle,
    }, // CLAP1_DETECTED
    {
        clap2_pending_clap_detect,
        idle,
        clap2_pending_timer300_expire,
        idle,
    } // CLAP2_PENDING
};

void setup()
{
    pinMode(s_led_pin, OUTPUT);
    pinMode(s_microphone_sensor, INPUT);
    digitalWrite(s_led_pin, LOW);
    Serial.begin(9600);
}

void loop()
{
    events event = NONE;

    if (millis() - s_timer300 >= 300 && s_timer300_active)
    {
        event = TIMER300_EXPIRE;
        Serial.println("timer300_expire");
        delay(50);
    }

    if (millis() - s_timer100 >= 100 && s_timer100_active)
    {
        event = TIMER100_EXPIRE;
        Serial.println("timer100_expire");
        delay(50);
    }

    if (digitalRead(s_microphone_sensor))
    {
        event = CLAP_DETECT;
        Serial.println("clap_detect");
        delay(50);
    }

    automata[s_crnt_state][event]();
}