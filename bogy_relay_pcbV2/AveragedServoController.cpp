#include "AveragedServoController.h"

AveragedServoController::AveragedServoController(int sensorPin, int servoPin, int sampleCount, unsigned long intervalMs)
  : sensorPin(sensorPin), servoPin(servoPin), sampleCount(sampleCount),
    index(0), samplesFull(false), lastSampleTime(0), sampleInterval(intervalMs),angleLimit(180), enabled(true)
{
  samples = new int[sampleCount];
}

AveragedServoController::~AveragedServoController() {
  delete[] samples;
}

void AveragedServoController::begin() {
  pinMode(sensorPin, INPUT);
  servo.attach(servoPin);
}

void AveragedServoController::setEnabled(bool state) {
  enabled = state;
  if (!enabled) {
    servo.write(96); // Stop servo movement if disabled ( idont know whay 90 not give 1.5ms pulse maybe becuse the vcc change to ESC
  }
}

void AveragedServoController::enable() {
  setEnabled(true);
}

void AveragedServoController::disable() {
  setEnabled(false);
}

void AveragedServoController::setMaxAngle(int maxAngle) {
  angleLimit = constrain(maxAngle, 0, 180);
}

void AveragedServoController::clearMaxAngle() {
  angleLimit = 180;
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
    int angle = map(avg, 100, 800, 90,angleLimit); 
    //Serial.println("send: " + String(angle));

    servo.write(angle);
    samplesFull = false;
  }
}
