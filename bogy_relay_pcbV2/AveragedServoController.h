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
<<<<<<< HEAD
    int angleLimit = 180;
=======
    //int angleLimit = 180;
    int minPulse;   // ESC minimum pulse width (us)
    int maxPulse;   // ESC maximum pulse width (us)
    int maxAllowedPulse; // Maximum allowed pulse width (us)
>>>>>>> 1714032 (new pwm work - completed)

    Servo servo;

  public:
<<<<<<< HEAD
    AveragedServoController(int sensorPin, int servoPin, int sampleCount = 10, unsigned long intervalMs = 5);
=======
    AveragedServoController(int sensorPin, int servoPin, int sampleCount = 10, unsigned long intervalMs = 5,int minPulse = 1500,
      int maxPulse = 2000);
>>>>>>> 1714032 (new pwm work - completed)
    ~AveragedServoController();

    void begin();
    void update();

    void setEnabled(bool state);
    void enable();
    void disable();

<<<<<<< HEAD
    void setMaxAngle(int maxAngle);
    void clearMaxAngle();
=======
    void setMaxPulse(int maxPulseUs);
    void clearMaxPulse();

    //void setMaxAngle(int maxAngle);
    //void clearMaxAngle();
>>>>>>> 1714032 (new pwm work - completed)
};
