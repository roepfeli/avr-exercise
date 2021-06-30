#include <Arduino_FreeRTOS.h>

#include <semphr.h>

TaskHandle_t button_handle_task;
TaskHandle_t blink_handle_task;

SemaphoreHandle_t semaphore;

void setup()
{
    xTaskCreate(blink_task, "Blink", 128, NULL, 2, &blink_handle_task);
    xTaskCreate(button_task, "Button", 128, NULL, 3, &button_handle_task);
    semaphore = xSemaphoreCreateBinary();
    Serial.begin(9600);
}

void loop() { }

void blink_task(void* pvParameters)
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    while (true)
    {
        if (xSemaphoreTake(semaphore, 200 / portTICK_PERIOD_MS) == pdTRUE)
        {
            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        }
    }
}

void button_task(void* pvParameters)
{
    pinMode(24, INPUT);

    // activate internal pull-up resistor:
    PORTA |= (1 << PA2);

    while (true)
    {
        if (!digitalRead(24))
        {
            Serial.println("Button pressed.");
            xSemaphoreGive(semaphore);
            vTaskDelay(200 / portTICK_PERIOD_MS);
        }
    }
}