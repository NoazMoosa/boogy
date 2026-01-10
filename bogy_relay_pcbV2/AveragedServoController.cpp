#include "AveragedServoController.h"

<<<<<<< HEAD
AveragedServoController::AveragedServoController(int sensorPin, int servoPin, int sampleCount, unsigned long intervalMs)
  : sensorPin(sensorPin), servoPin(servoPin), sampleCount(sampleCount),
    index(0), samplesFull(false), lastSampleTime(0), sampleInterval(intervalMs),angleLimit(180), enabled(true)
=======
AveragedServoController::AveragedServoController(int sensorPin, int servoPin, int sampleCount, unsigned long intervalMs, int minPulse,
  int maxPulse)
  : sensorPin(sensorPin), servoPin(servoPin), sampleCount(sampleCount),
    index(0), samplesFull(false), lastSampleTime(0), 
    sampleInterval(intervalMs), minPulse(minPulse), 
    maxPulse(maxPulse), maxAllowedPulse(maxPulse), enabled(true)
>>>>>>> 1714032 (new pwm work - completed)
{
  samples = new int[sampleCount];
}

AveragedServoController::~AveragedServoController() {
  delete[] samples;
}

void AveragedServoController::begin() {
  pinMode(sensorPin, INPUT);
<<<<<<< HEAD
  servo.attach(servoPin);
=======
  servo.attach(servoPin, minPulse, maxPulse);

  // ARM sequence – mandatory for ESC
  servo.writeMicroseconds(minPulse);
  delay(3000);
>>>>>>> 1714032 (new pwm work - completed)
}

void AveragedServoController::setEnabled(bool state) {
  enabled = state;
  if (!enabled) {
<<<<<<< HEAD
    servo.write(96); // Stop servo movement if disabled ( idont know whay 90 not give 1.5ms pulse maybe becuse the vcc change to ESC
=======
    servo.writeMicroseconds(minPulse); // Set to minimum pulse when disabled
>>>>>>> 1714032 (new pwm work - completed)
  }
}

void AveragedServoController::enable() {
  setEnabled(true);
}

void AveragedServoController::disable() {
  setEnabled(false);
}

<<<<<<< HEAD
void AveragedServoController::setMaxAngle(int maxAngle) {
  angleLimit = constrain(maxAngle, 0, 180);
}

void AveragedServoController::clearMaxAngle() {
  angleLimit = 180;
=======
void AveragedServoController::setMaxPulse(int maxPulseUs) {
  maxAllowedPulse = constrain(maxPulseUs, minPulse, maxPulse);
}

void AveragedServoController::clearMaxPulse() {
  maxAllowedPulse = maxPulse;
>>>>>>> 1714032 (new pwm work - completed)
}

void AveragedServoController::update() {
  unsigned long currentMillis = millis();
  // Sensor sampling at fixed interval
  if (currentMillis - lastSampleTime >= sampleInterval) {
    lastSampleTime = currentMillis;

    samples[index++] = analogRead(sensorPin);
    if (index >= sampleCount) {
      index = 0;
      samplesFull = true;
    }
  }

  // If enough samples collected and controller is enabled
  if (samplesFull && enabled) {
    long sum = 0;
    for (int i = 0; i < sampleCount; i++) {
      sum += samples[i];
    }

    int avg = sum / sampleCount;
    //Serial.println("analog: " + String(avg));
    avg = constrain(avg, 100, 800); 
<<<<<<< HEAD
    int angle = map(avg, 100, 800, 90,angleLimit); 
    //Serial.println("send: " + String(angle));

    servo.write(angle);
=======
   // Map sensor value directly to ESC pulse width
    int pulseWidth = map(avg, 100, 800, minPulse, maxAllowedPulse);
    pulseWidth = constrain(pulseWidth, minPulse, maxAllowedPulse);

    servo.writeMicroseconds(pulseWidth);
>>>>>>> 1714032 (new pwm work - completed)
    samplesFull = false;
  }
}
