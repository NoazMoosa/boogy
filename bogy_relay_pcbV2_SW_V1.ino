#include <Servo.h>


// Define pins for Arduino Uno.
const int relayOnPin = A4;     // Pin 27 for Relay On
const int relayOffPin = A3;    // Pin 26 for Relay Off
const int temp_bat1 = A1;      // Pin24 
const int temp_bat2 = A2;      // Pin25 
const int temp_relay = A0;     // Pin23 
const int throttlePin = A7;    // Pin 22 for Throttle Input
const int motorPWM = 3;        // Pin1 for Motor PWM (or any other PWM pin)
const int voltagePin = A6;     // Pin 19 for Voltage Sensing


struct NTC {
  String name_ntc;
  int Threshold;
  int NTC_pin;
};

// Variables
NTC NTCs[3]={
  {"bat1",50,temp_bat1},  //NTCs[0]
  {"bat1",50,temp_bat2},  //NTCs[1]
  {"raley",30,temp_relay} //NTCs[2]
};

int   throttleValue = 0;
int   motorSpeed = 0;
int   voltageReading = 0;
float Input_voltage=0;
float temperature_relay=0;
bool  relay_sate=false;
int   error_code=0;

//functions 
void turen_relay(bool state);
bool check_temperatur( NTC ntc);

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
  delay(2000);
}



void loop() {
Serial.print(" error_code: ");  
Serial.println(error_code);
 
if(error_code==0){
   relay_sate=turen_relay(true,relay_sate);
}

voltageReading = analogRead(voltagePin); // 0-1023
Input_voltage = (voltageReading / 1023.0) * 5.0*6.23;
Serial.print(" Voltage: ");
Serial.println(Input_voltage);

  // Check if the input voltage is below 16V
  if (Input_voltage < 16) {
    // Turn off the relay
    relay_sate = turen_relay(false,relay_sate);
    error_code = 1; 
  }
  else error_code = 0;  //relay_sate = turen_relay(true,relay_sate); 

  
  // temperature
  for(int i=0;i<3;i++){
    if(check_temperatur(NTCs[i])==true){
      relay_sate = turen_relay(false,relay_sate);
      error_code = i+1;
    }
  }
delay(50);
}


bool check_temperatur( NTC X){
   float temperature=0;
   float thermistorResistance=0;
   const int B_CONSTANT=3940;
     
   // Read the analog value (0-1023)
   // Calculate the thermistor resistance using voltage divider formula
   thermistorResistance = (10000 * (analogRead(X.NTC_pin) * (5 / 1023.0))) / (5 - (analogRead(X.NTC_pin) * (5 / 1023.0)));
   // Calculate the temperature using the Steinhart-Hart equation (simplified version)
   temperature = (1.0 / (1.0 / 298.15 + (1.0 / B_CONSTANT) * log(thermistorResistance / 10000.0)))- 273.15;

   Serial.println("th: " + String(X.Threshold)+ "temp: " + String(temperature));
   //Serial.print(X.Threshold);
   //Serial.println(temperature);

   if (temperature > X.Threshold) return true; 
   else return false;
}

// returen the state of the relat true is condaction and false is not condaction 
bool turen_relay(bool state,bool previous_state ){
  if (state == true && previous_state== false ){
    // Turn on the relay
    digitalWrite(relayOnPin, HIGH);
    delay(50);
    digitalWrite(relayOnPin, LOW);
    delay(1000);
    return true;
  }
  if(state == false && previous_state== true ) {
    // Turn off the relay
    digitalWrite(relayOffPin, HIGH);
    delay(50);
    digitalWrite(relayOffPin, LOW);
    delay(1000);
    return false;
  } 
  return previous_state;  
}
