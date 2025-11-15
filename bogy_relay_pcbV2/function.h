#pragma once
#include <Arduino.h>
#include "Pins.h"
#include "AveragedServoController.h"

extern bool relayState;
extern AveragedServoController servoCtrl;
void turn_relay(bool start);
void pwm_stop(bool yes);
void limit_pwm(int level);
