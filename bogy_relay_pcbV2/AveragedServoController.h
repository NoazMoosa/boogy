#pragma once
#include <Arduino.h>
#include <Servo.h>

class AveragedServoController {
  private:
    int sensorPin;
    int servoPin;
    int sampleCount;
    int* samples;
    int index;
    bool samplesFull;
    unsigned long lastSampleTime;
    unsigned long sampleInterval;
    bool enabled = true;
    int angleLimit = 180;

    Servo servo;

  public:
    AveragedServoController(int sensorPin, int servoPin, int sampleCount = 10, unsigned long intervalMs = 5);
    ~AveragedServoController();

    void begin();
    void update();

    void setEnabled(bool state);
    void enable();
    void disable();

    void setMaxAngle(int maxAngle);
    void clearMaxAngle();
};
