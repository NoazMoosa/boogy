#include <Servo.h>
#include <TimerOne.h>
#include "DHT.h"
#include "ErrorHandler.h"
#include "TemperatureHandler.h"
#include "Pins.h"


// volatile for shared variables between ISR and loop().
volatile int error_code = 0;  // Global variable to store value



// Define sensor type and pin
/*struct NTC {
  String name;
  int threshold;
  int pin;
};*/

// Variables
/*NTC NTCs[3]={
  {"bat1",50,temp_bat1},  //NTCs[0]
  {"bat2",50,temp_bat2},  //NTCs[1]
  {"raley",30,temp_relay} //NTCs[2]
};*/

ErrorHandler* handlers[5];

handlers[0] = new TemperatureAlert(1);
handlers[1] = new LowVoltage(2);
handlers[2] = new CriticalVoltage(3);
handlers[3] = new HighHumidity(4);
handlers[4] = new CommunicationAlert(5);

int   throttleValue = 0;
int   motorSpeed = 0;
int   voltageReading = 0;
float inputVoltage=0;
float temperatureRelay=0;
bool  relayState=false;


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

  if (error_code == 0 && relayState == false) turn_relay(true);

  handler = error_handler[error_code];

  handler.report_error();
  handler.handle_error();

  
  switch(error_code) {
    case 1:
      Serial.println("Battery 1 over temperature!");
      report_error(error_code)
      turn_relay(false)
      break;
    case 2:
      Serial.println("Battery 2 over temperature!");
      report_error(error_code)
      limit_pwm();
      break;
    case 3:
      Serial.println("Relay over temperature!")
      report_error(error_code)
      break;
    default: 
    report_error(error_code)
      if (relayState == false) {
        turn_relay(true);
      }
      break;
  }
  // Read the throttle value (0-1023) and map it to motor speed (0-255)
  throttleValue = analogRead(throttlePin); // Read the throttle value
  motorSpeed = map(throttleValue, 0, 1023, 0, 255); // Map to motor speed (0-255)
  // Set the motor speed using PWM
  analogWrite(motorPWM, motorSpeed); // Set the motor speed using PWM
  // Print the throttle value and motor speed for debugging
  Serial.print("Throttle Value: ");
  Serial.print(throttleValue);
  Serial.print(", Motor Speed: ");
  Serial.println(motorSpeed);

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
  voltageReading = analogRead(voltagePin); // 0-1023
  inputVoltage = (voltageReading / 1023.0) * 5.0*6.23;

  Serial.print("Voltage: ");
  Serial.println(inputVoltage);

  if (inputVoltage < 16) {
    // Turn off the relay
    turn_relay(false);
    error_code = 1; 
  }
  else error_code = 0;  //relayState = turn_relay(true); 
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
  
  relayState = start;
}

// interrupt function that check all the temperture and humidety 
void test(){
  
}

vo



handle_error(err_code) {
  switch (expression)
  {
  case constant expression:
    /* code */
    break;
  
  default:
    break;
  }
}

void hwait_until_resolved(err_code) {
  switch (expression)
  {
  case constant expression:
    /* code */
    break;
  
  default:
    break;
  }
}

class temp_handler : abs_handler {
  error_code = 4;

  void report_error() {
    Serial.println("Relay over temperature!");
    sound();
  }
}
