#pragma once

#include <stdint.h>

void adc_init(int pin);

uint16_t adc_read_analog();
