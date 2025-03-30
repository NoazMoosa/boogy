#include <Servo.h>
#include <TimerOne.h>
#include "DHT.h"

// volatile for shared variables between ISR and loop().
volatile int error_code = 0;  // Global variable to store value


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
  String name;
  int threshold;
  int pin;
};

// Variables
NTC NTCs[3]={
  {"bat1",50,temp_bat1},  //NTCs[0]
  {"bat2",50,temp_bat2},  //NTCs[1]
  {"raley",30,temp_relay} //NTCs[2]
};

int   throttleValue = 0;
int   motorSpeed = 0;
int   voltage_reading = 0;
float input_voltage=0;
float temperature_relay=0;
bool  relay_state=false;


//functions 
bool is_over_temp(NTC ntc);

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

// interrupt
 // Set Timer1-TCNT1 to CTC Mode -Clear Timer on Compare Match
 TCCR1A = 0;
 TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);  // CTC mode, Prescaler = 1024

 // OCR1A for ~286ms (closest possible value)
 OCR1A = 4465;  // (286ms ≈ 0.286s × 15625 ticks/s)
 TIMSK1 |= (1 << OCIE1A);  // Enable Compare Match A Interrupt


//  // use timer1 for interrupt. 
//  Timer1.initialize(1000);
//  Timer1.attachInterrupt(test());
//   

  // Start serial monitor for debugging
  Serial.begin(9600);
//  dht.begin();
  delay(2000);
}


void loop() {
  Serial.print("error_code: ");  
  Serial.println(error_code);

  if (error_code == 0 && relay_state == false) turn_relay(true);
  
  check_voltage();
  temperature_validation();
    
 // Reading temperature or humidity takes about 250 milliseconds!
 // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
//  float h = dht.readHumidity();
//  // Read temperature as Celsius (the default)
//  float t = dht.readTemperature();
  delay(50);
}

int check_voltage() {
  voltage_reading = analogRead(voltagePin); // 0-1023
  input_voltage = (voltage_reading / 1023.0) * 5.0*6.23;

  Serial.print("Voltage: ");
  Serial.println(input_voltage);

  if (input_voltage < 16) {
    // Turn off the relay
    turn_relay(false);
    error_code = 1; 
  }
  else error_code = 0;  //relay_state = turn_relay(true); 
}

void temperature_validation() {
  for(int i=0; i<3; i++){
    if(is_over_temp(NTCs[i])) {
      turn_relay(false);
      error_code = i+1;
    }
  }
}

bool is_over_temp(NTC X){
   float temperature=0;
   float thermistor_resistance=0;
   const int B_CONSTANT=3940;
     
   // Read the analog value (0-1023)
   // Calculate the thermistor resistance using voltage divider formula
   thermistor_resistance = (10000 * (analogRead(X.pin) * (5 / 1023.0))) / (5 - (analogRead(X.pin) * (5 / 1023.0)));
   // Calculate the temperature using the Steinhart-Hart equation (simplified version)
   temperature = (1.0 / (1.0 / 298.15 + (1.0 / B_CONSTANT) * log(thermistor_resistance / 10000.0)))- 273.15;

   Serial.println("sensor: " + X.name + ", th: " + String(X.threshold)+ ", temp: " + String(temperature));
   //Serial.print(X.threshold);
   //Serial.println(temperature);

   // 
   return temperature > X.threshold;
}

// return the state of the relay true is conduction and false is not conduction turn
void turn_relay(bool start){
  if(start) {
    digitalWrite(relayOnPin, HIGH);
    delay(50);
    digitalWrite(relayOnPin, LOW);
    delay(1000);
  }
  else {
    digitalWrite(relayOffPin, HIGH);
    delay(50);
    digitalWrite(relayOffPin, LOW);
    delay(1000);
  }  
  
  relay_state = start;
}

// interrupt function that check all the temperture and humidety 
void test(){
  
}
