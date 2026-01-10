#include "HumidityHandler.h"
// #include <cmath>  // For isnan()
#include <math.h>

HumidityHandler::HumidityHandler(float minHumidity, float maxHumidity, int errorCode)
    : ErrorHandler(errorCode),
      dht(humidityDataPin, DHT22),
      humidity(0.0f),
      minHumidity(minHumidity),
      maxHumidity(maxHumidity)
{
    pinMode(humidityVccPin, OUTPUT);
    pinMode(humidityGndPin, OUTPUT);

    powerOffSensor();
    delay(100);
    powerOnSensor();

    dht.begin();
    active = false;
    sensor_ok = true;
}

void HumidityHandler::powerOnSensor()
{
    digitalWrite(humidityGndPin, LOW);
    delay(10); // Ensure ground is stable
    digitalWrite(humidityVccPin, HIGH);
    // DHT22 stabilization time
    delay(1000);
}

void HumidityHandler::powerOffSensor()
{
    digitalWrite(humidityVccPin, LOW);
    digitalWrite(humidityGndPin, LOW);
}

void HumidityHandler::resetSensor()
{
    powerOffSensor();
    delay(100);
    powerOnSensor();
}

void HumidityHandler::check()
{
    humidity = dht.readHumidity();

    // Sensor failure
    if (isnan(humidity)) {
        //active = true;
        Serial.println("sensor_fail");
        sensor_ok = false;
        return;
    }

    // Humidity out of range
    if (humidity > maxHumidity) {
        Serial.println("Humidity out of range");
        Serial.println(humidity);
        active = true;
        react_type("critical");
    }
}

void HumidityHandler::handle()
{
    // All handling is done via react_type()
}

void HumidityHandler::report_error() const
{
    Serial.print("[HUMIDITY ERROR] Code: ");
    Serial.print(error_code);
    Serial.print(" | Humidity: ");
    Serial.println(humidity);
}
