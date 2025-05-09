#include "ErrorHandler.h"
#include <Arduino.h> 
#include "Pins.h"

class VoltageHandler : public ErrorHandler {
    private:

        volatile float inputVoltage = 0.0;
        volatile    int voltageReading = 0;
        String type;
        float threshold_shutdown = 16.0;
        float threshold_limit = 20.0;
        volatile    bool ok_shutdown = false; // true if the voltage is low and need to shutdown the system
        volatile  bool ok_limit = false; // true if the voltage is low and need to limit the pwm

        
    public:
    VoltageHandler(int code) : ErrorHandler(code) {}

        void report_error(int code) const override;
        void handle() override; 
        void check() override;  // Check if the error condition is met
        

        ~VoltageHandler() override = default;
};