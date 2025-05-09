#include "ErrorHandler.h"
#include <Arduino.h> 
#include "Pins.h"

class TemperatureHandler : public ErrorHandler {
    private:

        static const int number_NTC = 3;

        struct NTC {
            String name;
            String type;
            float threshold;
            int pin;
            volatile bool ok ; // true if the temperature is ok, false if it is not
            volatile float temperature; // Temperature value 
            volatile bool known ; // true if the temperature is known, false if it is not
        };

        NTC NTCs[number_NTC] = {
            {"bat1","critical", 50.0, temp_bat1,true,25.0,false},  //NTCs[0]
            {"bat2","critical", 50.0, temp_bat2,true,25.0,false},  //NTCs[1]
            {"relay","critical", 30.0, temp_relay,true,25.0,false} //NTCs[2]
        };
        
    public:
        TemperatureHandler(int code) : ErrorHandler(code) {}

        void report_error(int message) const override;
        void handle() override; 
        void check() override;  // Check if the error condition is met
        bool is_over_temp(NTC& X); // Check if the temperature is over the threshold


        ~TemperatureHandler() override = default;
};