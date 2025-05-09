#pragma once
#include <Arduino.h>
#include "Pins.h"

extern bool relayState;

void turn_relay(bool start);
void pwm_stop();
void limit_pwm();
