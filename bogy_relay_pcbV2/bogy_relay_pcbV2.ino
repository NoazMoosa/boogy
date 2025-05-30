#include <Servo.h>
#include <TimerOne.h>
#include "DHT.h"
#include "ErrorHandler.h"
#include "TemperatureHandler.h"
#include "Pins.h"
#include "function.h"
#include "VoltageHandler.h"
#include "AveragedServoController.h"

volatile int error_code = 0;  // Global variable to store value


int   throttleValue = 0;
int   motorSpeed = 0;
int   voltageReading = 0;
float inputVoltage=0;
bool  relayState=false;

VoltageHandler VH(0);
TemperatureHandler TH(0);
AveragedServoController servoCtrl(throttlePin, motorPWM);


void setup() {
  // Set pin modes
  pinMode(relayOnPin, OUTPUT);
  pinMode(relayOffPin, OUTPUT);
  pinMode(temp_bat1, INPUT);
  pinMode(temp_bat2, INPUT);
  pinMode(temp_relay, INPUT);
  pinMode(throttlePin, INPUT);
  pinMode(motorPWM, OUTPUT);
  pinMode(voltagePin, INPUT);

  // Initialize the relay off
  digitalWrite(relayOnPin, LOW);
  digitalWrite(relayOffPin, HIGH);
  delay(50);
  digitalWrite(relayOffPin, LOW); 

  // Start serial monitor for debugging
  Serial.begin(9600);
  servoCtrl.begin();
//dht.begin();
  delay(2000);
}


void loop() {

  VH.check(); // Check voltage
  VH.handle(); // Handle voltage error
  TH.check(); // Check temperature
  TH.handle(); // Handle temperature error
  TH.report_error(); // Report temperature error if any
  VH.report_error(); // Report voltage error if any
  delay(10); // Delay for 10ms

  if(VH.get_error_code() != 2 && TH.get_error_code() == 0 && !relayState) { // Check if there is no error
    turn_relay(true); // Turn on the relay
  }
  else if (VH.get_error_code() == 0 && TH.get_error_code() == 0 && relayState ) { // Check if there is no error
    servoCtrl.clearMaxAngle(); // anable full power
    servoCtrl.enable();
  }
  servoCtrl.update();
}
