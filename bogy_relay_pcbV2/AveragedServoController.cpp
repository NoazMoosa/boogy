#include "AveragedServoController.h"

AveragedServoController::AveragedServoController(int sensorPin, int servoPin, int sampleCount, unsigned long intervalMs)
  : sensorPin(sensorPin), servoPin(servoPin), sampleCount(sampleCount),
    index(0), samplesFull(false), lastSampleTime(0), sampleInterval(intervalMs)
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
    servo.write(90); // Stop servo movement if disabled
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
    int angle = map(avg, 100, 800, angleLimit,90);
    angle = constrain(angle, 90, angleLimit);

    servo.write(angle);
    samplesFull = false;
  }
}
