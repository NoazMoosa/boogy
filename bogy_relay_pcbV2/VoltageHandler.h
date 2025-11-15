#include "ErrorHandler.h"
#include "SimpleDFPlayer.h"
#include <Arduino.h> 
#include "Pins.h"

class VoltageHandler : public ErrorHandler {
    private:

        SimpleDFPlayer* player;

        volatile float inputVoltage = 0.0;
        volatile    int voltageReading = 0;
        String type;
        float threshold_shutdown = 18.5;
        float threshold_limit = 21.0;
        volatile    bool ok_shutdown = false; // true if the voltage is low and need to shutdown the system
        volatile  bool ok_limit = false; // true if the voltage is low and need to limit the pwm

        
    public:
    VoltageHandler(int code, SimpleDFPlayer* dfp) : ErrorHandler(code),player(dfp) {}

        void report_error() const override;
        void handle() override; 
        void check() override;  // Check if the error condition is met
        

        ~VoltageHandler() override = default;
};
