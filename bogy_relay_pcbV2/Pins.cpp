#include "Pins.h"

// Define pins for Arduino Uno.
const int relayOnPin   = A3;    // Pin 26 for Relay On
const int relayOffPin  = A4;    // Pin 27 for Relay Off
const int temp_bat1    = A1;    // Pin 24 for Battery 1 Temperature
const int temp_bat2    = A2;    // Pin 25 for Battery 2 Temperature
const int temp_relay   = A0;    // Pin 23 for Relay Temperature
const int throttlePin  = A7;    // Pin 22 for Throttle Input
const int motorPWM     = 3;   // Pin 1 for Motor PWM (or any other PWM pin)
const int voltagePin   = A6;    // Pin 19 for Voltage Sensing
// const int humidityDataPin = 9;   // PB1 pin 13
// const int humidityVccPin  = 10;  // PB2 pin 14   (PB0 pin 12 is D8 used for POC board)
// const int humidityGndPin  = 5;   // PD5 pin 9

// used for POC board
const int humidityDataPin = 5;   // PD5 pin 9 
const int humidityVccPin  = 10;  // PB2 pin 14   (PB0 pin 12 is D8 used for POC board)
const int humidityGndPin  = 9;   // PB1 pin 13

