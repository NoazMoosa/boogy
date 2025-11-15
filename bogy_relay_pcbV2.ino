#include <Servo.h>
#include <TimerOne.h>
#include "DHT.h"
#include "ErrorHandler.h"
#include "TemperatureHandler.h"
#include "Pins.h"
#include "function.h"
#include "VoltageHandler.h"
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

volatile int error_code = 0;  // Global variable to store value


int   throttleValue = 0;
int   motorSpeed = 0;
int   voltageReading = 0;
float inputVoltage=0;
bool  relayState=false;

SoftwareSerial mySerial(255, 12); // RX-nopin, TX =D12 PB4 for DFPlayer Mini
DFRobotDFPlayerMini myDFPlayer;

VoltageHandler VH(0);
TemperatureHandler TH(0, &myDFPlayer);



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

  myDFPlayer.begin(mySerial); // Initialize DFPlayer Mini
  myDFPlayer.volume(30); // Set volume to a reasonable level (0-30)

//  dht.begin();
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

  if(VH.get_error_code() == 0 && TH.get_error_code() == 0 && !relayState) { // Check if there is no error
    turn_relay(true); // Turn on the relay
  }

}