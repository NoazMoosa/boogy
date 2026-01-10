#pragma once
#ifndef HUMIDITY_HANDLER_H
#define HUMIDITY_HANDLER_H

#include <Arduino.h>
#include "DHT.h"
#include "ErrorHandler.h"
#include "Pins.h"

class HumidityHandler : public ErrorHandler {
public:
    HumidityHandler(float minHumidity,
                    float maxHumidity,
                    int errorCode);

    void check() override;                // Check if humidity error condition is met
    void handle() override;               // Handle humidity error
    void report_error() const override;   // Report humidity error
    void resetSensor();                   // Reset DHT22 power
    
private:
    void powerOnSensor();                 // Power ON DHT22
    void powerOffSensor();                // Power OFF DHT22
    

    DHT dht;
    float humidity;
    const float minHumidity; 
    const float maxHumidity; 
    bool sensor_ok;                  // Sensor status
};

#endif // HUMIDITY_HANDLER_H